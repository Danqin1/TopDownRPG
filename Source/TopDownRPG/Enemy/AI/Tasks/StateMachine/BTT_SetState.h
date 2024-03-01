// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TopDownRPG/TopDownRPG.h"
#include "BTT_SetState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_SetState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECharacterState> NewState;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
