// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/AbilityComponent.h"
#include "Components/CombatComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/PlayerStatsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "TopDownRPG/UI/DamageIndicatorActor.h"
#include "TopDownRPG/UI/HUD/PlayerHUD.h"
#include "RPGCharacter.generated.h"

UCLASS(Blueprintable)
class ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Sword Trace")
	float SwordTraceRadius = 20;
	UPROPERTY(EditDefaultsOnly, Category = "Sword Trace")
	float SwordTraceDelay = 0.05;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UPlayerSettings* Settings = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Indication")
	TSubclassOf<ADamageIndicatorActor> DamageIndicator;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UAIPerceptionStimuliSourceComponent* StimulusSourceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	TArray<IIDamageable*> DamagedActors;

	bool bIsTracingSword = false;
	float CurrentDamage = 0;
	
protected:
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	ARPGCharacter();
	
	UPROPERTY(EditDefaultsOnly)
	UPlayerStatsComponent* PlayerStatsComponent;
	UPROPERTY(EditDefaultsOnly)
	UAbilityComponent* AbilityComponent;
	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent* InventoryComponent;
	UPROPERTY(EditDefaultsOnly)
	UCombatComponent* CombatComponent;
	UPROPERTY()
	UPlayerHUD* PlayerHUD;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	void StartSwordTrace();
	void EndSwordTrace();
	void ModifyDamage(float NewDamage);
	void ClearDamageModifier();
	void TryDamageByAbility(const FVector Position, float Damage, const float Range = 10);
};

