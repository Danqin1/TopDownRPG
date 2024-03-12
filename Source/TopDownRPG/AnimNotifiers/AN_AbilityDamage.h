// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_AbilityDamage.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAN_AbilityDamage : public UAnimNotify
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Damage = 50;
	UPROPERTY(EditAnywhere)
	float Range = 300;
	UPROPERTY(EditAnywhere)
	FVector ActorOffset = FVector(150,0,100);
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
