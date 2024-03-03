// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTopDownRPG, Log, All);

DECLARE_MULTICAST_DELEGATE(FOnDieEvent);

template<typename T>
static FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindFirstObjectSafe<UEnum>(*enumName);
	return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
}

UENUM(BlueprintType)
enum ECastType
{
	None,
	Direction,
	Target
};

UENUM(BlueprintType)
enum ECharacterState
{
	Nothing,
	Chasing,
	Attacking,
	Skill,
	Interaction,
	Cutscene,
	Dead
};