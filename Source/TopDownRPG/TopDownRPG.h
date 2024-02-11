// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTopDownRPG, Log, All);

UENUM(BlueprintType)
enum CastType
{
	None,
	Direction,
	Target
};