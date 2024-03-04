#pragma once

#include "FQuest.generated.h"

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name = "";
	UPROPERTY(EditAnywhere)
	FString Description = "";
	UPROPERTY(EditAnywhere)
	bool IsSecondary = false;
	UPROPERTY(EditAnywhere)
	bool IsCompleted = false;
};
