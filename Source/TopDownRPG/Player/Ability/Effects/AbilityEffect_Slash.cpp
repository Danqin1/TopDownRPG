// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Slash.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TopDownRPG/Player/TopDownRPGCharacter.h"


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
		if(ATopDownRPGCharacter* Character = Cast<ATopDownRPGCharacter>(Caster))
		{
			Character->ModifyDamage(Damage);
			
			FTimerHandle TimerHandle;
			float AnimTime = SlashAnimation->GetSectionLength(0);
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Character]()
			{
				if(Character)
				{
					Character->ClearDamageModifier();
				}
			}, AnimTime, false, AnimTime);
		}
		
		Caster->GetMovementComponent()->StopMovementImmediately();
		Caster->PlayAnimMontage(SlashAnimation);
	}
	Super::Activate(Caster);
}
