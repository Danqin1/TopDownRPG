// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Slash.h"

#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AAbility_Slash::AAbility_Slash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AAbility_Slash::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbility_Slash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility_Slash::Activate(ACharacter* Caster)
{
	Super::Activate(Caster);
}

