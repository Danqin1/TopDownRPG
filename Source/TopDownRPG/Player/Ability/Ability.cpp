// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"

#include "GameFramework/Character.h"
#include "TopDownRPG/Player/Components/PlayerStatsComponent.h"


// Sets default values
AAbility::AAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

bool AAbility::CanUseAbility()
{
	if(UPlayerStatsComponent* Stats = CasterCharacter->FindComponentByClass<UPlayerStatsComponent>())
	{
		return Stats->GetMana() > ManaCost;
	}
	return false;
}

void AAbility::Activate(ACharacter* Caster)
{
	CasterCharacter = Caster;
	if(CanUseAbility())
	{
		if(UPlayerStatsComponent* Stats = CasterCharacter->FindComponentByClass<UPlayerStatsComponent>())
		{
			Stats->RemoveMana(ManaCost);
		}
		
		for (auto Effect : Effects)
		{
			const FTransform Transform = TargetCharacter ? TargetCharacter->GetTransform() : Caster->GetTransform();
			AAbilityEffect* AbilityEffect = GetWorld()->SpawnActor<AAbilityEffect>(Effect, Transform);
		}
	}

	Destroy();
}