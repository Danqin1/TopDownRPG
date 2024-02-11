// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "RPGActorComponentBase.h"
#include "Components/ActorComponent.h"
#include "TopDownRPG/Player/TopDownRPGPlayerController.h"
#include "TopDownRPG/Player/Ability/Ability.h"
#include "TopDownRPG/Player/Ability/Casting/DirectionCaster.h"
#include "TopDownRPG/Player/Ability/Casting/TargetCaster.h"
#include "AbilityComponent.generated.h"

UCLASS()
class TOPDOWNRPG_API UAbilityComponent : public URPGActorComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityComponent();
	virtual void SetupComponent() override;
	virtual void Dispose() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability1Action;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability2Action;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability3Action;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability4Action;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability5Action;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* Ability6Action;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability1;
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability2;
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability3;
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability4;
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability5;
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<AAbility> Ability6;

	UPROPERTY(EditDefaultsOnly, Category="Casting")
	TSubclassOf<ADirectionCaster> DirectionalCasterClass;
	UPROPERTY(EditDefaultsOnly, Category="Casting")
	TSubclassOf<ATargetCaster> TargetCasterClass;
	
	UPROPERTY()
	AAbility* CurrentAbility;
	UPROPERTY()
	ACaster* CurrentCastingIndicator;
	UPROPERTY()
	ATopDownRPGPlayerController* PlayerController;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnAbility1();
	UFUNCTION()
	void OnAbility2();
	UFUNCTION()
	void OnAbility3();
	UFUNCTION()
	void OnAbility4();
	UFUNCTION()
	void OnAbility5();
	UFUNCTION()
	void OnAbility6();

	void TryUseAbility(TSubclassOf<AAbility> Ability);
	void SpawnAbility(TSubclassOf<AAbility> Ability);
	void CastAbility(AAbility* Ability);
};