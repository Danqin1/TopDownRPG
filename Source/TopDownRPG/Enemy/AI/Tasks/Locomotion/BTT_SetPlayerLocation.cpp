// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TopDownRPG/DevDebug.h"

UBTT_SetPlayerLocation::UBTT_SetPlayerLocation()
{
	NodeName = TEXT("Set Player Location");
}

EBTNodeResult::Type UBTT_SetPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		if(APawn* Pawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetPlayer.SelectedKeyName)))
		{
			FNavLocation Loc;
			if(NavSys->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), NavTolerance, Loc))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				DevDebug::OnScreenLog("Cant find point on NavMesh");
			}
		}
		else
		{
			DevDebug::OnScreenLog("Target is not Pawn");
		}
	}

	return EBTNodeResult::Failed;
}
