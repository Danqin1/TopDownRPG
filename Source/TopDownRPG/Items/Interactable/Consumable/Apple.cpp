// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"

#include "TopDownRPG/Player/TopDownRPGPlayerController.h"


// Sets default values
AApple::AApple()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AApple::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnBeginCursorOver.AddDynamic(this, &AApple::CustomOnBeginMouseOver);
	BoxCollider->OnEndCursorOver.AddDynamic(this, &AApple::CustomOnEndMouseOver);
}

void AApple::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	BoxCollider->OnBeginCursorOver.RemoveDynamic(this, &AApple::CustomOnBeginMouseOver);
	BoxCollider->OnEndCursorOver.RemoveDynamic(this, &AApple::CustomOnEndMouseOver);
	Super::EndPlay(EndPlayReason);
}

void AApple::Interact(ATopDownRPGCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Interaction");
	UPlayerStatsComponent* PlayerStatsComponent = Character->GetComponentByClass<UPlayerStatsComponent>();
	if(PlayerStatsComponent)
	{
		PlayerStatsComponent->AddHP(HPValue);
	}

	Destroy();
}

