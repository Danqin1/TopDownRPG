// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SwordTrace.h"

#include "TopDownRPG/Player/RPGCharacter.h"

void UAN_SwordTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if(auto* Player = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Player->CombatComponent->StartSwordTrace();
	}
}

void UAN_SwordTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Player = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Player->CombatComponent->EndSwordTrace();
	}
}
