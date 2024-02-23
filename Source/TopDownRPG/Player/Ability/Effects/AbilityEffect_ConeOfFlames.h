// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "TopDownRPG/Player/Ability/AbilityEffect.h"
#include "AbilityEffect_ConeOfFlames.generated.h"

UCLASS()
class TOPDOWNRPG_API AAbilityEffect_ConeOfFlames : public AAbilityEffect
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityEffect_ConeOfFlames();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UAnimMontage* CastAnimation;
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UNiagaraSystem* FlamesEffect;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
