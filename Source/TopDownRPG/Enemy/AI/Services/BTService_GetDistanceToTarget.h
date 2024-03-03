// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_GetDistanceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTService_GetDistanceToTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsInRange;
	UPROPERTY(EditAnywhere)
	float Distance = 300;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
