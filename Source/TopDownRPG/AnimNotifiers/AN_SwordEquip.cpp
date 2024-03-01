// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SwordEquip.h"

#include "TopDownRPG/Player/RPGCharacter.h"

void UAN_SwordEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(ARPGCharacter* Character = Cast<ARPGCharacter>(MeshComp->GetOwner()))
	{
		if(bShouldEquip)
		{
			Character->InventoryComponent->EquipWeapon();
		}
		else
		{
			Character->InventoryComponent->HideWeapon();
		}
	}
}
