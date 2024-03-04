// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UW_Interact.generated.h"

/**
 * 
 */
UCLASS(HideDropdown)
class TOPDOWNRPG_API UUW_Interact : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* InteractionText;

public:
	void SetInteractionText(FString text);
};
