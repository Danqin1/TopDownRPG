// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_QuestSlot.h"

void UUW_QuestSlot::NativeConstruct()
{
	if(Button)
	{
		Button->OnClicked.AddDynamic(this, &UUW_QuestSlot::OnClick);
		
	}
	Super::NativeConstruct();
}

void UUW_QuestSlot::Populate(FQuest Quest)
{
	TargetQuest = Quest;
	Name->SetText(FText::FromString(Quest.Name));
}

void UUW_QuestSlot::OnClick()
{
	if(OnClicked.IsBound())
	{
		OnClicked.Broadcast(TargetQuest);
	}
}
