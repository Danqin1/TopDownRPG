// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Slash.h"

#include "GameFramework/GameSession.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "TopDownRPG/Player/TopDownRPGCharacter.h"


// Sets default values
AAbilityEffect_Slash::AAbilityEffect_Slash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->SetSphereRadius(150);
	SphereComponent->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AAbilityEffect_Slash::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbilityEffect_Slash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;
	if(LifeTime >= 1)
	{
		Destroy();
	}
}

void AAbilityEffect_Slash::Activate(ACharacter* Caster)
{
	if(Caster && SlashAnimation)
	{
		Caster->GetMovementComponent()->StopMovementImmediately();
		Caster->PlayAnimMontage(SlashAnimation);
	}
		
	TArray<AActor*> OverlappingActors;
	SphereComponent->GetOverlappingActors(OverlappingActors);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if(Cast<ATopDownRPGCharacter>(OverlappingActor))
		{
			continue;
		}
			
		FVector Location = OverlappingActor->GetActorLocation();
		FVector LaunchDir = Location - GetActorLocation();
		LaunchDir.Normalize();
			
		if (IIDamageable* Damageable = Cast<IIDamageable>(OverlappingActor))
		{
			if(ACharacter* Character = Cast<ACharacter>(OverlappingActor))
			{
				Character->LaunchCharacter(LaunchDir * PushEnemiesStrength, false, false);
			}
				
			Damageable->Damage(Damage);
		}
	}
}
