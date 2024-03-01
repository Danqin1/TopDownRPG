// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"

#include "TopDownRPG/Player/RPGPlayerController.h"


// Sets default values
AApple::AApple()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AApple::BeginPlay()
{
	Super::BeginPlay();
}

void AApple::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AApple::Interact(ARPGCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Interaction");
	UPlayerStatsComponent* PlayerStatsComponent = Character->PlayerStatsComponent;
	if(PlayerStatsComponent)
	{
		PlayerStatsComponent->AddHP(HPValue);
	}

	Destroy();
}

