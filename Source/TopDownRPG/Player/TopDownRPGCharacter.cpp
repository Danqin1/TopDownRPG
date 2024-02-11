// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownRPGCharacter.h"

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
#include "Kismet/KismetSystemLibrary.h"
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
}

void ATopDownRPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(PlayerHUDClass)
	{
		ATopDownRPGPlayerController* PC = GetController<ATopDownRPGPlayerController>();
		check(PC);
		PlayerHUD = CreateWidget<UPlayerHUD>(PC, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();
	}

	TSet<UActorComponent*>  Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		if(URPGActorComponentBase* RPGComponent = Cast<URPGActorComponentBase>(Component))
		{
			RPGComponent->SetupComponent();
		}
	}
}

void ATopDownRPGCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	TSet<UActorComponent*>  Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		if(URPGActorComponentBase* RPGComponent = Cast<URPGActorComponentBase>(Component))
		{
			RPGComponent->Dispose();
		}
	}
	Super::EndPlay(EndPlayReason);
}

void ATopDownRPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	
	if(bIsTracingSword)
	{
		TArray<FHitResult> OutResults;
		FVector Start = GetMesh()->GetSocketLocation("FX_weapon_base");
		FVector End =  GetMesh()->GetSocketLocation("FX_weapon_tip");
		TArray<AActor*> ToIgnore;
		
		UKismetSystemLibrary::SphereTraceMulti(GetWorld(),  Start, End , SwordTraceRadius,
			TraceTypeQuery1,
			false,
			ToIgnore,
			EDrawDebugTrace::ForDuration, OutResults, true, FLinearColor::Red, FLinearColor::Green, SwordTraceDelay);

		for (FHitResult OutResult : OutResults)
		{
			if(!DamagedActors.Contains(OutResult.GetActor()))
			{
				if(auto* Enemy = Cast<IIDamageable>(OutResult.GetActor()))
				{
					Enemy->Damage(InventoryComponent->GetCurrentWeaponDamage());
					DamagedActors.Add(OutResult.GetActor());
				}
			}
		}
	}
}

void ATopDownRPGCharacter::SetAutoAttack(bool enabled)
{
	if(auto* AnimBP = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance()))
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
