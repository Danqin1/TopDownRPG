// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "TopDownRPG/Interfaces/Enemy.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class TOPDOWNRPG_API AEnemyCharacter : public ACharacter, public IIDamageable, public IEnemy
{
private:
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual void OnHit(AActor* Hitter, FVector HitPosition, FVector HitVelocity) override;
	virtual void Damage(float Damage) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual bool CanDamage() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Data")
	FName EnemyDataName = "DefaultEnemy";
	
	UPROPERTY(EditDefaultsOnly, Category="Data")
	UDataTable* Data;

	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* LifeBar;

	float MaxHP = 0;
	float CurrentHP = 0;
	float CurrentDamage = 0;

	bool bIsDead = false;

	void Die();
};
