// Fill out your copyright notice in the Description page of Project Settings.


#include "ICharacterState.h"


// Add default functionality here for any IIPlayerState functions that are not pure virtual.
ECharacterState IICharacterState::GetState()
{
	return Nothing;
}

void IICharacterState::SetState(ECharacterState NewState)
{
}

void IICharacterState::ClearState(ECharacterState State)
{
}
