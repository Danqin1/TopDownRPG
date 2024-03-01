// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/TopDownRPG.h"
#include "UObject/Interface.h"
#include "ICharacterState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChanged, ECharacterState, State);

// This class does not need to be modified.
UINTERFACE()
class UICharacterState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class TOPDOWNRPG_API IICharacterState
{
	GENERATED_BODY()
	
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FStateChanged OnStateChanged;
	
	virtual ECharacterState GetState();
	virtual void SetState(ECharacterState NewState);
	virtual void ClearState(ECharacterState State);
};
