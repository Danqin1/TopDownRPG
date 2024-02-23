// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "TopDownRPG/DevDebug.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	if(ATopDownRPGCharacter* Player  = Cast<ATopDownRPGCharacter>(TryGetPawnOwner()))
	{
		Character = Player;
		if(UInventoryComponent* Inventory = Player->FindComponentByClass<UInventoryComponent>())
		{
			InventoryComponent = Inventory;
		}
	}
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(Character)
	{
		bIsAccelerating = Character->GetVelocity().Length() > AccelerationThreshold;
		bIsAttacking = Character->bIsAttacking;
		if(InventoryComponent)
		{
			bHasSword = InventoryComponent->HasEquippedWeapon();
		}
	}
}
