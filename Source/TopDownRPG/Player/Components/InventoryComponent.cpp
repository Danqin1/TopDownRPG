// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ComponentUtils.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	WeaponMeleeHandle = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeleeHandle");
	WeaponMeleeBackIdle = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeleeBackIdle");

	WeaponMeleeHandle->SetCollisionProfileName("NoCollision");
	WeaponMeleeBackIdle->SetCollisionProfileName("NoCollision");
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ARPGCharacter* Character  = Cast<ARPGCharacter>(GetOwner()))
	{
		WeaponMeleeHandle->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "weapon_r");
		WeaponMeleeBackIdle->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "weapon_back");

		Character->OnStateChanged.AddDynamic(this, &UInventoryComponent::OnStateChanged);
	}

	if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(EquipAction, ETriggerEvent::Started, this, &UInventoryComponent::ToggleMelee);
	}
}

void UInventoryComponent::OnStateChanged(ECharacterState State)
{
	if(State == Dragon)
	{
		WeaponMeleeHandle->SetVisibility(false);
		WeaponMeleeBackIdle->SetVisibility(false);
	}
	else
	{
		WeaponMeleeHandle->SetVisibility(true);
		WeaponMeleeBackIdle->SetVisibility(true);
	}
}

float UInventoryComponent::GetCurrentWeaponDamage()
{
	return 20;// TODO add weapons control
}

void UInventoryComponent::ToggleMelee()
{
	if(ARPGCharacter* Character  = Cast<ARPGCharacter>(GetOwner()))
	{
		if(Character->GetState() == Dragon)
		{
			return;
		}
		if(!bEquippedWeapon)
		{
			if(GetWeaponAnim)
			{
				Character->PlayAnimMontage(GetWeaponAnim);
			}
		}
		else
		{
			if(HideWeaponAnim)
			{
				Character->PlayAnimMontage(HideWeaponAnim);
			}
		}
	}
}

void UInventoryComponent::EquipWeapon()
{
	WeaponMeleeHandle->SetStaticMesh(WeaponMeleeBackIdle->GetStaticMesh());
	WeaponMeleeBackIdle->SetStaticMesh(nullptr);
	bEquippedWeapon = true;
}

void UInventoryComponent::HideWeapon()
{
	WeaponMeleeBackIdle->SetStaticMesh(WeaponMeleeHandle->GetStaticMesh());
	WeaponMeleeHandle->SetStaticMesh(nullptr);
	bEquippedWeapon = false;
}

