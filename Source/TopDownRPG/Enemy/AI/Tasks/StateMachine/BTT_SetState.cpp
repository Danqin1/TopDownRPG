// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetState.h"

#include "AIController.h"
#include "TopDownRPG/Enemy/EnemyCharacter.h"

EBTNodeResult::Type UBTT_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Character->SetState(NewState);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
