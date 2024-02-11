// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Caster.h"
#include "GameFramework/Actor.h"
#include "TargetCaster.generated.h"

UCLASS()
class TOPDOWNRPG_API ATargetCaster : public ACaster
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATargetCaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
