// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPGCharacter.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY()
	ATopDownRPGCharacter* Character = nullptr;
	UPROPERTY()
	UInventoryComponent* InventoryComponent = nullptr;
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bHasSword = true;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsAccelerating = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AccelerationThreshold = 50;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
