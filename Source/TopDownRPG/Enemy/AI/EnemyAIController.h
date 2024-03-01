// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TopDownRPG/Database/FEnemyData.h"
#include "TopDownRPG/Enemy/EnemyCharacter.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TOPDOWNRPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	FName Param_TargetPlayer = "TargetPlayer";
	FName Param_Airborne = "IsAirborne";
	FName Param_State = "State";
	
	FDelegateHandle AirborneHandle;
public:
	// Sets default values for this actor's properties
	AEnemyAIController();

protected:
	UPROPERTY(Transient)
	TObjectPtr<AEnemyCharacter> ControllerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetForgotten(AActor* Actor);
	
	UFUNCTION()
	void OnCharacterAirborne(bool isAirborne);

	UFUNCTION()
	void OnStateChanged(ECharacterState State);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetAIData(FEnemyData* Data);
};
