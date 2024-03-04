// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "DamageIndicatorActor.generated.h"

UCLASS(HideDropdown)
class TOPDOWNRPG_API ADamageIndicatorActor : public AActor
{
	GENERATED_BODY()
	
	float ShowTime = 0;
	
public:
	// Sets default values for this actor's properties
	ADamageIndicatorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float MaxShowTime = 2;
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float UpVelocity = 0.02;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* DamageWidget;

	void Show(float Damage);
};
