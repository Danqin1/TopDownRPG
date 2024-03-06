// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_QuestGIver.h"

#include "Kismet/GameplayStatics.h"

void UUW_QuestGIver::NativeConstruct()
{
	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}

	if(CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UUW_QuestGIver::OnCloseButton);
	}
	Super::NativeConstruct();
}

void UUW_QuestGIver::NativeDestruct()
{
	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
	if(CloseButton)
	{
		CloseButton->OnClicked.RemoveDynamic(this, &UUW_QuestGIver::OnCloseButton);
	}
	Super::NativeDestruct();
}

void UUW_QuestGIver::Populate(TArray<FQuest> Quests)
{
	TargetQuests = Quests;
	for (FQuest Quest : Quests)
	{
		auto* QuestSlot = CreateWidget<UUW_QuestSlot>(GetWorld(), SlotClass);
		QuestsList->AddChild(QuestSlot);
		QuestSlot->Populate(Quest);
		TargetSlots.Add(QuestSlot);
		QuestSlot->OnClicked.AddDynamic(this, &UUW_QuestGIver::OnQuestClicked);
	}
}

void UUW_QuestGIver::OnQuestClicked(FQuest Quest)
{
	CurrentShowing = Quest;
	QuestDescription->SetText(FText::FromString(Quest.Description));
}

void UUW_QuestGIver::OnCloseButton()
{
	for (UUW_QuestSlot* QuestSlot : TargetSlots)
	{
		QuestSlot->OnClicked.RemoveDynamic(this, &UUW_QuestGIver::OnQuestClicked);;
	}
	
	if(OnClose.IsBound())
	{
		OnClose.Broadcast();
	}
}

void UUW_QuestGIver::OnSelectButton()
{
}
