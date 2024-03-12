// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AN_TakeOffLaunch.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_TakeOffLaunch : public UAnimNotifyState
{
	GENERATED_BODY()

	bool bCanTakeOff = true;
	
	UPROPERTY(EditAnywhere)
	float LaunchForce = 500;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
