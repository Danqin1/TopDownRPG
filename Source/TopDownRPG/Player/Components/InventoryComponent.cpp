// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ComponentUtils.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	WeaponMeleeHandle = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeleeHandle");
	WeaponMeleeBackIdle = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeleeBackIdle");

	WeaponMeleeHandle->SetCollisionProfileName("NoCollision");
	WeaponMeleeBackIdle->SetCollisionProfileName("NoCollision");
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ACharacter* Character  = Cast<ACharacter>(GetOwner()))
	{
		WeaponMeleeHandle->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "weapon_r");
		WeaponMeleeBackIdle->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "weapon_back");
	}

	if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(EquipAction, ETriggerEvent::Started, this, &UInventoryComponent::ToggleMelee);
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UInventoryComponent::GetCurrentWeaponDamage()
{
	return 20;// TODO add weapons control
}

void UInventoryComponent::ToggleMelee()
{
	if(ACharacter* Character  = Cast<ACharacter>(GetOwner()))
	{
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

