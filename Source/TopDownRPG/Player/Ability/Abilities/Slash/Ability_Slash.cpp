// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Slash.h"

#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TopDownRPG/DevDebug.h"


// Sets default values
AAbility_Slash::AAbility_Slash()
{
	PrimaryActorTick.bCanEverTick = true;
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
	DevDebug::OnScreenLog("Slash recharge:" +FString::SanitizeFloat(RechargeTime), FColor::Black, .1);
}

void AAbility_Slash::Activate(ACharacter* Caster)
{
	Super::Activate(Caster);
}

