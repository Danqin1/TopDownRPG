// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_TakeOffLaunch.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAN_TakeOffLaunch::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if(auto* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if(Character->GetCharacterMovement()->IsFlying())
		{
			bCanTakeOff = false;
		}
		else
		{
			bCanTakeOff = true;
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		}
	}
}

void UAN_TakeOffLaunch::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
}

void UAN_TakeOffLaunch::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if(!bCanTakeOff)
	{
		return;
	}
	if(auto* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Character->SetActorLocation(FMath::Lerp(Character->GetActorLocation(), Character->GetActorLocation() + FVector(0,0,500),
			FrameDeltaTime * LaunchForce));
	}
}
