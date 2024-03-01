// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AN_DamageModifier.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_DamageModifier : public UAnimNotifyState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float Damage = 50;
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
