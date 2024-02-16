// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Lightning.h"

#include "TopDownRPG/Player/TopDownRPGCharacter.h"


// Sets default values
AAbility_Lightning::AAbility_Lightning()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_Lightning::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbility_Lightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility_Lightning::Activate(ACharacter* Caster)
{
	Super::Activate(Caster);
}
