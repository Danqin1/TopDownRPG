// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "EnhancedInputComponent.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCombatComponent::SetupComponent()
{
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
			bIsAttacking = false;
			lastAttackInputTime = 0;
		}
	}
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	
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
						if(++currentComboIndex >= NormalAttackComboAnimations.Num() || currentComboIndex >= ComboLock)
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

