// Fill out your copyright notice in the Description page of Project Settings.


#include "IGamepadNavigable.h"

#include "TopDownRPG/DevDebug.h"


// Add default functionality here for any IIGamepadNavigable functions that are not pure virtual.
void IIGamepadNavigable::MoveUp()
{
	DevDebug::OnScreenLog("MoveUp");
}

void IIGamepadNavigable::MoveDown()
{
	DevDebug::OnScreenLog("MoveDown");
}

void IIGamepadNavigable::MoveLeft()
{
	DevDebug::OnScreenLog("MoveLeft");
}

void IIGamepadNavigable::MoveRight()
{
	DevDebug::OnScreenLog("MoveRight");
}
