// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/Player/Ability/Ability.h"
#include "Ability_ConeOfFlames.generated.h"

UCLASS()
class TOPDOWNRPG_API AAbility_ConeOfFlames : public AAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility_ConeOfFlames();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate(ACharacter* Caster) override;
};
