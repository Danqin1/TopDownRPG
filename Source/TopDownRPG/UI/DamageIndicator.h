// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageIndicator.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UDamageIndicator : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* DamageText;
};
