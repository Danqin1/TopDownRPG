// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Chase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_Chase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float AcceptableRadius = 300;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
