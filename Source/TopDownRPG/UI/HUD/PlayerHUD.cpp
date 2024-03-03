// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::SetHP(float Percent)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UPlayerHUD::SetMana(float Percent)
{
	if(ManaBar)
	{
		ManaBar->SetPercent(Percent);
	}
}

void UPlayerHUD::SetAction(int slot, FString name, UTexture2D* icon)
{
	switch (slot)
	{
	case 0:
		Action_0->Icon->SetBrushFromTexture(icon, false);
		Action_0->Name->SetText(FText::FromString(name));
		break;
	case 1:
		Action_1->Icon->SetBrushFromTexture(icon, false);
		Action_1->Name->SetText(FText::FromString(name));
		break;
	case 2:
		Action_2->Icon->SetBrushFromTexture(icon, false);
		Action_2->Name->SetText(FText::FromString(name));
		break;
	case 3:
		Action_3->Icon->SetBrushFromTexture(icon, false);
		Action_3->Name->SetText(FText::FromString(name));
		break;
	}
}

void UPlayerHUD::StateChanged(ECharacterState State)
{
	Action_0->SetVisibility(State == Skill ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Action_1->SetVisibility(State == Skill ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Action_2->SetVisibility(State == Skill ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Action_3->SetVisibility(State == Skill ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	FString enumName = "ECharacterState";
	StateDebug->SetText(FText::FromString(EnumToString(enumName, State)));
}

void UPlayerHUD::ShowInteraction(bool canInteract)
{
	if(canInteract && InteractionGroup->GetVisibility() == ESlateVisibility::Hidden)
	{
		InteractionGroup->SetVisibility(ESlateVisibility::Visible);
	}
	if(!canInteract && InteractionGroup->GetVisibility() == ESlateVisibility::Visible)
	{
		InteractionGroup->SetVisibility(ESlateVisibility::Hidden);
	}
}

UW_ActionSlot* UPlayerHUD::GetUISlot(int index)
{
	switch (index)
	{
	case 0: return Action_0;
	case 1: return Action_1;
	case 2: return Action_2;
	case 3: return Action_3;
		default: return nullptr;
	}
}


