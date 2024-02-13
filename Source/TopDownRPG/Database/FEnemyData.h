#pragma once

#include "Engine/DataTable.h"
#include "FEnemyData.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> AnimBP;

	UPROPERTY(EditAnywhere, Category="Combat")
	float MaxHP = 100;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float Damage = 5;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float MoveSpeed = 500;
};
