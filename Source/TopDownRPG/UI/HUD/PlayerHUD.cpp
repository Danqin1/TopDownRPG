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
	case 4:
		PrimaryAction->Icon->SetBrushFromTexture(icon, false);
		PrimaryAction->Name->SetText(FText::FromString(name));
		break;
	case 5:
		SecondaryAction->Icon->SetBrushFromTexture(icon, false);
		SecondaryAction->Name->SetText(FText::FromString(name));
		break;
	}
}


