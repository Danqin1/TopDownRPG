// Fill out your copyright notice in the Description page of Project Settings.


#include "Caster.h"


// Sets default values
ACaster::ACaster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	MeshComponent->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void ACaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

