// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "RPGActorComponentBase.h"
#include "CombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNRPG_API UCombatComponent : public URPGActorComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatComponent();

	virtual void SetupComponent() override;
	virtual void Dispose() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void TryContinueCombo();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TArray<UAnimMontage*> NormalAttackComboAnimations;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UAnimMontage* DodgeAnim;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	int ComboLock = 2;

	float lastAttackInputTime = 0;
	bool bIsAttacking = false;
	int currentComboIndex = 0;
	bool bShouldContinueCombo = false;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAttack();

	UFUNCTION()
	void OnDodge();
};
