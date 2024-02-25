// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Slash.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values
AAbilityEffect_Slash::AAbilityEffect_Slash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbilityEffect_Slash::BeginPlay()
{
	Super::BeginPlay();
}

void AAbilityEffect_Slash::Activate(ACharacter* Caster)
{
	if(Caster && SlashAnimation)
	{
		if(ARPGCharacter* CasterCharacter = Cast<ARPGCharacter>(Caster))
		{
			CasterCharacter->ModifyDamage(Damage);
			
			FTimerHandle TimerHandle;
			float AnimTime = SlashAnimation->GetSectionLength(0);
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, CasterCharacter]()
			{
				if(CasterCharacter)
				{
					CasterCharacter->ClearDamageModifier();
				}
				Destroy();
			}, AnimTime, false, AnimTime);
		}
		
		Caster->GetMovementComponent()->StopMovementImmediately();
		Caster->PlayAnimMontage(SlashAnimation);
	}
}
