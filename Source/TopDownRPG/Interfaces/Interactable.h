// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void SetAsTarget(bool isTargeted) PURE_VIRTUAL()
	UFUNCTION()
	virtual void Interact(ACharacter* Character) PURE_VIRTUAL()
	UFUNCTION()
	virtual void InteractionFinished() PURE_VIRTUAL()
	UFUNCTION()
	virtual bool CanInteract() {return true;}
	UFUNCTION()
	virtual float GetInteractionDistance() { return 400;}
};
