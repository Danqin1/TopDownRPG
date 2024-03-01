// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PerformRandomAttack.h"

#include "AIController.h"
#include "TopDownRPG/Enemy/EnemyCharacter.h"

EBTNodeResult::Type UBTT_PerformRandomAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Character->PlayAnimMontage(Attacks[FMath::RandRange(0, Attacks.Num() - 1)]);
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
