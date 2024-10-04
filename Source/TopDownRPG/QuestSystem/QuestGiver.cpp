// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiver.h"

#include "TopDownRPG/Player/RPGCharacter.h"
#include "TopDownRPG/UI/Interaction/UW_Interact.h"


// Sets default values
AQuestGiver::AQuestGiver()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>("InteractionWidget");
	InteractionWidget->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	if(auto* UWInteract = Cast<UUW_Interact>(InteractionWidget->GetWidget()))
	{
		UWInteract->SetInteractionText("Get Quest");
	}
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(false);
	}
}

void AQuestGiver::Interact(ACharacter* Character)
{
	if(auto* RPGCharacter = Cast<ARPGCharacter>(Character))
	{
		InteractCharacter = RPGCharacter;
		InteractCharacter->SetState(Interaction);
		UIWidget = CreateWidget<UUW_QuestGIver>(GetWorld(), UIClass);
		UIWidget->OnClose.AddDynamic(this, &AQuestGiver::InteractionFinished);
		UIWidget->AddToViewport();
		UIWidget->Populate(Quests);
	}
}

void AQuestGiver::InteractionFinished()
{
	if(InteractCharacter)
	{
		InteractCharacter->ClearState(Interaction);
	}
	if(UIWidget)
	{
		UIWidget->OnClose.RemoveDynamic(this, &AQuestGiver::InteractionFinished);
		UIWidget->RemoveFromParent();
		UIWidget->Destruct();
		UIWidget = nullptr;
	}
}

void AQuestGiver::SetAsTarget(bool isTargeted)
{
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(isTargeted);
	}
}

