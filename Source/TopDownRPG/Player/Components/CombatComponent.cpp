// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TopDownRPG/Interfaces/Enemy.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCombatComponent::SetupComponent()
{
	if(auto* Character = Cast<ARPGCharacter>(GetOwner()))
	{
		CharacterMesh = Character->GetMesh();
		CharacterMovement = Character->GetCharacterMovement();
		InventoryComponent = Character->InventoryComponent;
	}
}

void UCombatComponent::Dispose()
{
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &UCombatComponent::OnAttack);
		Input->BindAction(DodgeAction, ETriggerEvent::Started, this, &UCombatComponent::OnDodge);
		Input->BindAction(TargetLockAction, ETriggerEvent::Started, this, &UCombatComponent::OnTargetLock);
	}
}

void UCombatComponent::OnAttack()
{
	if(!bIsAttacking)
	{
		if(ARPGCharacter* RPGPlayer = Cast<ARPGCharacter>(GetOwner()))
		{
			if(RPGPlayer->InventoryComponent->HasEquippedWeapon())
			{
				currentComboIndex = 0;
				lastAttackInputTime = RPGPlayer->PlayAnimMontage(NormalAttackComboAnimations[currentComboIndex]) / NormalAttackComboAnimations[currentComboIndex]->RateScale;
				bIsAttacking = true;
				bShouldContinueCombo = false;
			}
		}
	}
	else
	{
		bShouldContinueCombo = true;
	}
}

void UCombatComponent::OnDodge()
{
	if(DodgeAnim)
	{
		if(ARPGCharacter* RPGPlayer = Cast<ARPGCharacter>(GetOwner()))
		{
			RPGPlayer->StopAnimMontage();
			RPGPlayer->PlayAnimMontage(DodgeAnim);
			currentComboIndex = 0;
			bShouldContinueCombo = false;
			bIsAttacking = false;
			lastAttackInputTime = 0;
		}
	}
}

void UCombatComponent::OnTargetLock() 				//check if died?
{
	if(!LockTarget)
	{
		if(UCameraComponent* Camera = GetOwner()->GetComponentByClass<UCameraComponent>())
		{
			TArray<FHitResult> OutResults;
			FVector Start = Camera->GetComponentLocation();
			FVector End = Start + Camera->GetForwardVector() * 1000;
			TArray<AActor*> ToIgnore;
			ToIgnore.Add(GetOwner());
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

			UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, 150,
												   ObjectTypes,
												   false,
												   ToIgnore,
												   EDrawDebugTrace::ForDuration, OutResults, true, FLinearColor::Red,
												   FLinearColor::Green, 1);

			for (FHitResult OutResult : OutResults)
			{
				if(IEnemy* Enemy = Cast<IEnemy>(OutResult.GetActor()))
				{
					LockTarget = OutResult.GetActor();
					LockTargetDieHandle = Enemy->OnDie.AddUObject(this, &UCombatComponent::OnEnemyDied);
					return;
				}
			}
		}
	}
	else
	{
		// remove lock
		if(IEnemy* Enemy = Cast<IEnemy>(LockTarget))
		{
			Enemy->OnDie.Remove(LockTargetDieHandle);
		}
		LockTarget = nullptr;
	}
}

void UCombatComponent::OnEnemyDied()
{
	if(LockTarget)
	{
		LockTarget = nullptr;
	}
}

void UCombatComponent::StartSwordTrace()
{
	DamagedActors.Empty();
	CharacterMovement->MaxWalkSpeed = 100.f;
	bIsTracingSword = true;
	bCanSlowTime = true;
}

void UCombatComponent::EndSwordTrace()
{
	bIsTracingSword = false;
	bCanSlowTime = false;
	CharacterMovement->MaxWalkSpeed = 500.f;
}

void UCombatComponent::ModifyDamage(float NewDamage)
{
	//CurrentDamage = NewDamage;
}

void UCombatComponent::ClearDamageModifier()
{
	//CurrentDamage = InventoryComponent->GetCurrentWeaponDamage();
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	timeSLowDuration += DeltaTime;
	
	if(bTimeSlowed && timeSLowDuration > .02)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
		bTimeSlowed = false;
	}

	if (bIsTracingSword)
	{
		TArray<FHitResult> OutResults;
		FVector Start = CharacterMesh->GetSocketLocation("weapon_base");
		FVector End = CharacterMesh->GetSocketLocation("weapon_tip");
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
					Damageable->Damage(InventoryComponent->GetCurrentWeaponDamage());
					if (auto* Enemy = Cast<IEnemy>(Damageable))
					{
						FVector Location = OutResult.GetActor()->GetActorLocation();
						FVector LaunchDir = Location - GetOwner()->GetActorLocation();

						Enemy->OnHit(GetOwner(), OutResult.Location,
							LaunchDir * InventoryComponent->GetCurrentWeaponDamage());

						if(BloodVFX)
						{
							UNiagaraComponent* BloodFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,
								BloodVFX, OutResult.Location, UKismetMathLibrary::FindLookAtRotation(End, OutResult.Location),
								FVector(1.f, 1.f, 1.f), true, true,
								ENCPoolMethod::None, true);
						}

						if(!bTimeSlowed && bCanSlowTime)
						{
							UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2);
							timeSLowDuration = 0;
							bTimeSlowed = true;
							bCanSlowTime = false;
						}
					}

					if (DamageIndicator)
					{
						// self destroyed
						ADamageIndicatorActor* Damage = GetWorld()->SpawnActor<ADamageIndicatorActor>(
							DamageIndicator, OutResult.Location, FRotator::ZeroRotator);
						if (Damage)
						{
							Damage->Show(InventoryComponent->GetCurrentWeaponDamage());
						}
					}

					DamagedActors.Add(Damageable);
				}
			}
		}
	}
}

void UCombatComponent::TryContinueCombo()
{
	if(bIsAttacking)
	{
			if(bShouldContinueCombo)
			{
				if(ARPGCharacter* RPGPlayer = Cast<ARPGCharacter>(GetOwner()))
				{
					if(RPGPlayer->InventoryComponent->HasEquippedWeapon())
					{
						currentComboIndex++;
						if(!NormalAttackComboAnimations.IsValidIndex(currentComboIndex) || currentComboIndex >= ComboLock)
						{
							currentComboIndex = 0;
						}
						lastAttackInputTime = RPGPlayer->PlayAnimMontage(NormalAttackComboAnimations[currentComboIndex]) / NormalAttackComboAnimations[currentComboIndex]->RateScale;
						bShouldContinueCombo = false;
					}
				}
			}
			else
			{
				bIsAttacking = false;
			}
	}
}

AActor* UCombatComponent::GetLockTarget()
{
	return LockTarget;
}

void UCombatComponent::TryDamageByAbility(const FVector Position, float Damage, const float Range)
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

