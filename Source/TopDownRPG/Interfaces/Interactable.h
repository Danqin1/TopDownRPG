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
	virtual void SetAsTarget(bool isTargeted) PURE_VIRTUAL()
	virtual void Interact(ACharacter* Character) PURE_VIRTUAL()
	virtual void InteractionFinished() PURE_VIRTUAL()
	virtual bool CanInteract() {return true;}
	virtual float GetInteractionDistance() { return 400;}
};
