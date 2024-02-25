// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InventoryComponent.h"
#include "NiagaraSystem.h"
#include "RPGActorComponentBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "TopDownRPG/Player/HitCameraShake.h"
#include "TopDownRPG/UI/DamageIndicatorActor.h"
#include "CombatComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNRPG_API UCombatComponent : public URPGActorComponentBase
{
	GENERATED_BODY()

	bool bIsTracingSword = false;
	bool bTimeSlowed = false;
	float timeSLowDuration = 0;
	bool bCanSlowTime = false;
	
	UPROPERTY()
	TArray<IIDamageable*> DamagedActors;
	UPROPERTY()
	USkeletalMeshComponent* CharacterMesh;
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovement;
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
public:
	// Sets default values for this component's properties
	UCombatComponent();

	virtual void SetupComponent() override;
	virtual void Dispose() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void TryContinueCombo();
	AActor* GetLockTarget();
	void StartSwordTrace();
	void EndSwordTrace();
	void ModifyDamage(float NewDamage);
	void ClearDamageModifier();
	void TryDamageByAbility(const FVector Position, float Damage, const float Range = 10);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sword Trace")
	float SwordTraceRadius = 20;
	UPROPERTY(EditDefaultsOnly, Category = "Sword Trace")
	float SwordTraceDelay = 0.05;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* TargetLockAction;

	UPROPERTY(EditDefaultsOnly, Category = "Indication")
	TSubclassOf<ADamageIndicatorActor> DamageIndicator;

	UPROPERTY(EditDefaultsOnly, Category = "Indication")
	UNiagaraSystem* BloodVFX;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TArray<UAnimMontage*> NormalAttackComboAnimations;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UAnimMontage* DodgeAnim;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	int ComboLock = 2;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<UHitCameraShake> SwordHitCameraShake;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PushEnemiesStrength = 10;

	UPROPERTY()
	AActor* LockTarget = nullptr;
	FDelegateHandle LockTargetDieHandle;
	
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

	UFUNCTION()
	void OnTargetLock();

	UFUNCTION()
	void OnEnemyDied();
};
