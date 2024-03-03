// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"

#include "TopDownRPG/Player/RPGCharacter.h"
#include "TopDownRPG/Player/RPGPlayerController.h"
#include "TopDownRPG/Player/Components/PlayerStatsComponent.h"


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

void AApple::Interact(ACharacter* Character)
{
	Super::Interact(Character);
	
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Interaction");
	if(auto* RPGCharacter  = Cast<ARPGCharacter>(Character))
	{
		UPlayerStatsComponent* PlayerStatsComponent = RPGCharacter->PlayerStatsComponent;
		if(PlayerStatsComponent)
		{
			PlayerStatsComponent->AddHP(HPValue);
		}
	}

	Super::InteractionFinished();
	Destroy();
}

