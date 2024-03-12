// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_AbilityDamage.h"

#include "TopDownRPG/Player/Components/CombatComponent.h"

void UAN_AbilityDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(UCombatComponent* CombatComponent = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>())
	{
		CombatComponent->TryDamageByAbility(MeshComp->GetComponentLocation() + ActorOffset, Damage, Range);
	}
}
