// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Dash.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAbility_Dash::AAbility_Dash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_Dash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbility_Dash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility_Dash::Activate(ACharacter* Caster)
{
	Super::Activate(Caster);
	if(DashAnim)
	{
		Caster->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Caster->GetActorLocation(), CastLocation));
		Caster->GetCharacterMovement()->StopMovementImmediately();
		Caster->PlayAnimMontage(DashAnim);
	}
}

