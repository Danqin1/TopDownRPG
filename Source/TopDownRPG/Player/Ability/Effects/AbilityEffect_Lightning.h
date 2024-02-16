// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "TopDownRPG/Player/Ability/AbilityEffect.h"
#include "AbilityEffect_Lightning.generated.h"

UCLASS()
class TOPDOWNRPG_API AAbilityEffect_Lightning : public AAbilityEffect
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityEffect_Lightning();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UAnimMontage* CastAnimation;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UNiagaraSystem* OnPlayerEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UNiagaraSystem* OnTargetEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	float OnPlayerEffectDelay = 0.5;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	float OnTargetEffectDelay = 1;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	float OnPlayerEffectZOffset = 1;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DamageRange = 1;

	bool bIsActive = false;
	bool bFirstPlayed = false;
	float Time = 0;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate(ACharacter* Caster) override;
};
