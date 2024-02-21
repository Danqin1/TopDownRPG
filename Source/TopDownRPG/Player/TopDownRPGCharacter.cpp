// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownRPGCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "PlayerAnimInstance.h"
#include "TopDownRPGPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "TopDownRPG/DevDebug.h"
#include "TopDownRPG/Enemy/EnemyCharacter.h"
#include "TopDownRPG/Interfaces/IDamageable.h"

ATopDownRPGCharacter::ATopDownRPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->bEnableCameraLag = true;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PlayerHUD = nullptr;

	PlayerStatsComponent = CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("Player Stats"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	StimulusSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
}

void ATopDownRPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		ATopDownRPGPlayerController* PC = GetController<ATopDownRPGPlayerController>();
		check(PC);
		PlayerHUD = CreateWidget<UPlayerHUD>(PC, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();
	}

	TSet<UActorComponent*> Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		if (URPGActorComponentBase* RPGComponent = Cast<URPGActorComponentBase>(Component))
		{
			RPGComponent->SetupComponent();
		}
	}

	if (Settings)
	{
		CurrentDamage = Settings->MeleeBaseDamage;
	}
	else
	{
		DevDebug::OnScreenLog("Missing Player Settings!");
	}

	if(StimulusSourceComponent)
	{
		StimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimulusSourceComponent->RegisterWithPerceptionSystem();
	}
}

void ATopDownRPGCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	TSet<UActorComponent*> Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		if (URPGActorComponentBase* RPGComponent = Cast<URPGActorComponentBase>(Component))
		{
			RPGComponent->Dispose();
		}
	}
	Super::EndPlay(EndPlayReason);
}

void ATopDownRPGCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsTracingSword)
	{
		TArray<FHitResult> OutResults;
		FVector Start = GetMesh()->GetSocketLocation("FX_weapon_base");
		FVector End = GetMesh()->GetSocketLocation("FX_weapon_tip");
		TArray<AActor*> ToIgnore;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, SwordTraceRadius,
		                                       ObjectTypes,
		                                       false,
		                                       ToIgnore,
		                                       EDrawDebugTrace::None, OutResults, true, FLinearColor::Red,
		                                       FLinearColor::Green, SwordTraceDelay);

		for (FHitResult OutResult : OutResults)
		{
			if (auto* Damageable = Cast<IIDamageable>(OutResult.GetActor()))
			{
				if (!DamagedActors.Contains(Damageable))
				{
					Damageable->Damage(CurrentDamage);
					if (auto* Enemy = Cast<AEnemyCharacter>(Damageable))
					{
						FVector Location = Enemy->GetActorLocation();
						FVector LaunchDir = Location - GetActorLocation();
						FVector CutDir = OutResult.Location - End;

						Enemy->LaunchCharacter(
							LaunchDir * Settings->PushEnemiesStrength * CurrentDamage / Settings->MeleeBaseDamage,
							false, false);

						if(Settings->Blood_FX)
						{
							UNiagaraComponent* BloodFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,
								Settings->Blood_FX, OutResult.Location, UKismetMathLibrary::FindLookAtRotation(End, OutResult.Location),
								FVector(1.f, 1.f, 1.f), true, true,
								ENCPoolMethod::None, true);
						}
					}

					if (DamageIndicator)
					{
						// self destroyed
						ADamageIndicatorActor* Damage = GetWorld()->SpawnActor<ADamageIndicatorActor>(
							DamageIndicator, OutResult.Location, FRotator::ZeroRotator);
						if (Damage)
						{
							Damage->Show(CurrentDamage);
						}
					}

					DamagedActors.Add(Damageable);
				}
			}
		}
	}

	if(GetVelocity().Length() > 0.1)
	{
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);
	}
}

void ATopDownRPGCharacter::SetAutoAttack(bool enabled)
{
	if (auto* AnimBP = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimBP->bIsAttacking = enabled;
	}
}

void ATopDownRPGCharacter::StartSwordTrace()
{
	DamagedActors.Empty();
	bIsTracingSword = true;
}

void ATopDownRPGCharacter::EndSwordTrace()
{
	bIsTracingSword = false;
}

void ATopDownRPGCharacter::ModifyDamage(float NewDamage)
{
	CurrentDamage = NewDamage;
}

void ATopDownRPGCharacter::ClearDamageModifier()
{
	CurrentDamage = InventoryComponent->GetCurrentWeaponDamage();
}

void ATopDownRPGCharacter::TryDamageByAbility(const FVector Position, float Damage, const float Range)
{
	TArray<FHitResult> OutResults;
	TArray<AActor*> ToIgnore;
	DamagedActors.Empty();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Position, Position, Range,
	                                       ObjectTypes,
	                                       false,
	                                       ToIgnore,
	                                       EDrawDebugTrace::None, OutResults, true, FLinearColor::Red,
	                                       FLinearColor::Green, 2);

	for (FHitResult OutResult : OutResults)
	{
		if (auto* Damageable = Cast<IIDamageable>(OutResult.GetActor()))
		{
			if (!DamagedActors.Contains(Damageable))
			{
				Damageable->Damage(Damage);
				DamagedActors.Add(Damageable);
				if (DamageIndicator)
				{
					// self destroyed
					ADamageIndicatorActor* DamageIndicatorActor = GetWorld()->SpawnActor<ADamageIndicatorActor>(
						DamageIndicator, OutResult.Location, FRotator::ZeroRotator);
					if (DamageIndicatorActor)
					{
						DamageIndicatorActor->Show(Damage);
					}
				}
			}
		}
	}

	DamagedActors.Empty();
}
