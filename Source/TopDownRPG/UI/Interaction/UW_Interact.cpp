// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Interact.h"

void UUW_Interact::SetInteractionText(FString text)
{
	if(InteractionText)
	{
		InteractionText->SetText(FText::FromString(text));
	}
}
