// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNRPG_API UPlayerSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MinCameraDistance = 100;

	UPROPERTY(EditAnywhere)
	float MaxCameraDistance = 100;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 1;

	UPROPERTY(EditAnywhere)
	float MeleeAttackRange = 300;
};
