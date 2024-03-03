// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PerformAttack.h"

#include "AIController.h"
#include "TopDownRPG/Interfaces/EnemyCombat.h"

UBTT_PerformAttack::UBTT_PerformAttack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	bTickIntervals = 0.1;
}

void UBTT_PerformAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FUBTT_PerformAttackMemory* MyMemory = reinterpret_cast<FUBTT_PerformAttackMemory*>(NodeMemory);
	if(MyMemory->ElapsedTime >= MyMemory->WaitDuration)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		MyMemory->ElapsedTime += DeltaSeconds;
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	}
}

uint16 UBTT_PerformAttack::GetInstanceMemorySize() const
{
	return sizeof(FUBTT_PerformAttackMemory);
}

EBTNodeResult::Type UBTT_PerformAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(IEnemyCombat* Combat = Cast<IEnemyCombat>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		FUBTT_PerformAttackMemory* MyMemory = reinterpret_cast<FUBTT_PerformAttackMemory*>(NodeMemory);
		
		MyMemory->WaitDuration = Combat->Attack();
		MyMemory->ElapsedTime = 0;
		
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
