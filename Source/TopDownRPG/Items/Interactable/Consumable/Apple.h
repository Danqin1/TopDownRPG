// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/Items/Interactable/InteractableBase.h"
#include "Apple.generated.h"

UCLASS()
class TOPDOWNRPG_API AApple : public AInteractableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AApple();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Interact(ATopDownRPGCharacter* Character) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Consumable")
	float HPValue = 5;
};
