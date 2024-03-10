// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_TakeOffLaunch.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_TakeOffLaunch : public UAnimNotify
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float LaunchForce = 500;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
