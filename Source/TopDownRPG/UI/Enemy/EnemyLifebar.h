// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EnemyLifebar.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEnemyLifebar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UProgressBar* HPBar;
};
