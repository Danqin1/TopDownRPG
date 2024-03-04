// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "TopDownRPG/Interfaces/Interactable.h"
#include "TopDownRPG/Player/RPGCharacter.h"
#include "QuestGiver.generated.h"

UCLASS()
class TOPDOWNRPG_API AQuestGiver : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestGiver();

protected:
	UPROPERTY(Transient)
	ARPGCharacter* InteractCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* InteractionWidget;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact(ACharacter* Character) override;
	virtual void InteractionFinished() override;
	virtual void SetAsTarget(bool isTargeted) override;
};
