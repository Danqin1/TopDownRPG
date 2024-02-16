// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/Player/Ability/AbilityEffect.h"
#include "AbilityEffect_Slash.generated.h"

UCLASS()
class TOPDOWNRPG_API AAbilityEffect_Slash : public AAbilityEffect
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityEffect_Slash();
protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SlashAnimation = nullptr;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	virtual void Activate(ACharacter* Caster) override;
};
