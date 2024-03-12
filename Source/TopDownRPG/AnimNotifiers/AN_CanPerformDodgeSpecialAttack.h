// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AN_CanPerformDodgeSpecialAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_CanPerformDodgeSpecialAttack : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
