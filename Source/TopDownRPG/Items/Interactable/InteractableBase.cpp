// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values
AInteractableBase::AInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("InteractionWidget");
	InteractionWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	if(InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
	}
}

ARPGPlayerController* AInteractableBase::GetPlayerController()
{
	if(ARPGPlayerController* PC = Cast<ARPGPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return PC;
	}
	return nullptr;
}

void AInteractableBase::Interact(ACharacter* Character)
{
	if(auto* RPGCharacter = Cast<ARPGCharacter>(Character))
	{
		InteractCharacter = RPGCharacter;
		InteractCharacter->SetState(Interaction);
	}
}

void AInteractableBase::InteractionFinished()
{
	if(InteractCharacter)
	{
		InteractCharacter->ClearState(Interaction);
	}
}

void AInteractableBase::SetAsTarget(bool isTargeted)
{
	if(InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(isTargeted);
	}
}
