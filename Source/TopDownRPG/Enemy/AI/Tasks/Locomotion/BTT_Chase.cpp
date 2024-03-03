// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Chase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey())))
	{
		OwnerComp.GetAIOwner()->MoveToActor(Actor, AcceptableRadius);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return  EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
