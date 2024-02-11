// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class TOPDOWNRPG_API AEnemyCharacter : public ACharacter, public IIDamageable
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	virtual void Damage(float Damage) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
