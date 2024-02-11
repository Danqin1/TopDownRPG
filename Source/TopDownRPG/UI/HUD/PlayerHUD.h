// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "W_ActionSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* PrimaryAction;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* SecondaryAction;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* Action_0;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* Action_1;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* Action_2;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UW_ActionSlot* Action_3;
public:
	void SetHP(float Percent);
	void SetMana(float Percent);
	void SetAction(int slot, FString name, UTexture2D* icon);

	UW_ActionSlot* GetUISlot(int index);
};
