// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Lightning.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TopDownRPG/Player/TopDownRPGCharacter.h"


// Sets default values
AAbilityEffect_Lightning::AAbilityEffect_Lightning()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbilityEffect_Lightning::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityEffect_Lightning::Tick(float DeltaTime)
{
	if(bIsActive)
	{
		Time += DeltaTime;

		if(!bFirstPlayed && Time >= OnPlayerEffectDelay)
		{
			if(OnPlayerEffect && Character)
			{
				Character->GetMovementComponent()->StopMovementImmediately();
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnPlayerEffect,
					Character->GetActorLocation() + FVector::UpVector * OnPlayerEffectZOffset, FRotator::ZeroRotator,
					FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}
			bFirstPlayed = true;
		}

		if(Time >= OnTargetEffectDelay)
		{
			if(OnTargetEffect)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnTargetEffect, GetActorLocation(), FRotator::ZeroRotator,
					FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}

			if (auto* TDCharacter = Cast<ATopDownRPGCharacter>(Character))
			{
				TDCharacter->TryDamageByAbility(GetActorLocation(), Damage, DamageRange);
			}
			PrimaryActorTick.SetTickFunctionEnable(false);
			Destroy();
		}
	}
}

void AAbilityEffect_Lightning::Activate(ACharacter* Caster)
{
	Character = Caster;
	if(CastAnimation)
	{
		Character->PlayAnimMontage(CastAnimation);
	}
	bIsActive = true;
}

