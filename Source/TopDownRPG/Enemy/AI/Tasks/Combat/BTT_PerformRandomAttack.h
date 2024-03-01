// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_PerformRandomAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_PerformRandomAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> Attacks;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
