// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ActionSlot.h"

void UW_ActionSlot::UpdateRecharge(float progress)
{
	if(CooldownOverlay)
	{
		CooldownOverlay->SetPercent(progress);
	}
}
