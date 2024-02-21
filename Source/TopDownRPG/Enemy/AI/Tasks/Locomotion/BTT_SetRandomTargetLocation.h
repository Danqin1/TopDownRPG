// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_SetRandomTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_SetRandomTargetLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float RandomPointMaxDistance = 500;
public:
	explicit UBTT_SetRandomTargetLocation();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
