// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_TryContinueCombo.h"

#include "TopDownRPG/Player/RPGCharacter.h"

void UAN_TryContinueCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(ARPGCharacter* Character = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Character->CombatComponent->TryContinueCombo();
	}
}
