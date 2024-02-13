// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityEffect.generated.h"

UCLASS(Abstract)
class TOPDOWNRPG_API AAbilityEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityEffect();

	virtual void Activate(ACharacter* Caster);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float PushEnemiesStrength = 1000;

	UPROPERTY()
	ACharacter* Character;
};
