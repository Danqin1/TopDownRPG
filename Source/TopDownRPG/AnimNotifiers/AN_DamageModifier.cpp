// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_DamageModifier.h"

#include "TopDownRPG/Player/RPGCharacter.h"

void UAN_DamageModifier::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	if(auto* Character = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Character->CombatComponent->ModifyDamage(Damage);
	}
}

void UAN_DamageModifier::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Character = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		Character->CombatComponent->ClearDamageModifier();
	}
}
