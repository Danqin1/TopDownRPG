// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetDistanceToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TopDownRPG/DevDebug.h"

void UBTService_GetDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey())))
	{
		float Dist = FVector::Dist(Actor->GetActorLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()) ;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsInRange.SelectedKeyName, Dist < Distance);
	}
	else
	{
		DevDebug::OnScreenLog("No target", FColor::Red, 0.1);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsInRange.SelectedKeyName, false);
	}
}
