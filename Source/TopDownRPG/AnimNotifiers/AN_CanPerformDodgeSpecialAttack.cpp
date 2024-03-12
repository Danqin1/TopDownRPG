// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_CanPerformDodgeSpecialAttack.h"

#include "TopDownRPG/Player/RPGCharacter.h"


void UAN_CanPerformDodgeSpecialAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Player = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Player->CombatComponent->TryDodgeSpecialAttack();
	}
}