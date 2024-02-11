// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Slash.h"

#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Player/TopDownRPGCharacter.h"


// Sets default values
AAbilityEffect_Slash::AAbilityEffect_Slash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->SetSphereRadius(150);
	SphereComponent->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AAbilityEffect_Slash::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		TArray<AActor*> OverlappingActors;
		SphereComponent->GetOverlappingActors(OverlappingActors);
		for (AActor* OverlappingActor : OverlappingActors)
		{
			if(Cast<ATopDownRPGCharacter>(OverlappingActor))
			{
				continue;
			}
			FVector Dir = GetActorForwardVector();
			FVector Location = OverlappingActor->GetActorLocation();

			float Dot = FVector::DotProduct(Location - GetActorLocation(), Location);
			if (Dot > 0)
			{
				UGameplayStatics::ApplyDamage(OverlappingActor, Damage, nullptr, GetOwner(), nullptr);
			}
		}

		Destroy();
	});
}

// Called every frame
void AAbilityEffect_Slash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
