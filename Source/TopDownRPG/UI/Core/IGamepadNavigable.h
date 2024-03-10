// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGamepadNavigable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIGamepadNavigable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IIGamepadNavigable
{
	GENERATED_BODY()

protected:
	TArray<IIGamepadNavigable*> Navigables;
public:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};
