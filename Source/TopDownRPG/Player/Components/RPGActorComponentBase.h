// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGActorComponentBase.generated.h"


UCLASS(Abstract)
class TOPDOWNRPG_API URPGActorComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URPGActorComponentBase();

	virtual void SetupComponent() PURE_VIRTUAL()
	virtual void Dispose() PURE_VIRTUAL()
};
