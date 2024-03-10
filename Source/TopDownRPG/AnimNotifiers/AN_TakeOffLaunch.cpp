// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_TakeOffLaunch.h"

#include "GameFramework/Character.h"

void UAN_TakeOffLaunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Character->LaunchCharacter(FVector::UpVector * LaunchForce, false, true);
	}
}
