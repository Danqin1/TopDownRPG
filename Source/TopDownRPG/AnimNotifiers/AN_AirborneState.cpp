// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_AirborneState.h"

#include "TopDownRPG/Player/RPGCharacter.h"

void UAN_AirborneState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if(auto* Player = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Player->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void UAN_AirborneState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Player = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}
