// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/Items/ItemBase.h"
#include "TopDownRPG/Items/Interfaces/Interactable.h"
#include "TopDownRPG/Player/TopDownRPGPlayerController.h"
#include "InteractableBase.generated.h"

UCLASS()
class TOPDOWNRPG_API AInteractableBase : public AItemBase, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float MaxInteractionRange = 200;
	UPROPERTY(EditDefaultsOnly, Category="Hover")
	UMaterialInstance* NormalMat;

	UPROPERTY(EditDefaultsOnly, Category="Hover")
	UMaterialInstance* HoverMat;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ATopDownRPGPlayerController* GetPlayerController();

	UFUNCTION()
	virtual void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	virtual void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
public:
	virtual void OnClicked() override;
	virtual void Interact(ATopDownRPGCharacter* Character) override;
};
