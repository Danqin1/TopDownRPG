// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Caster.generated.h"

UCLASS()
class TOPDOWNRPG_API ACaster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACaster();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Casting")
	UStaticMeshComponent* MeshComponent;
public:
	UPROPERTY(EditDefaultsOnly, Category="Casting")
	float Length = 5;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
