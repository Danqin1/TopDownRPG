// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SwordEquip.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_SwordEquip : public UAnimNotify
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	bool bShouldEquip = true;
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
