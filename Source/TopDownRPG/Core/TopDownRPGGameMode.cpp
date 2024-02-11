// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownRPGGameMode.h"
#include "TopDownRPG//Player/TopDownRPGPlayerController.h"
#include "TopDownRPG/Player/TopDownRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownRPGGameMode::ATopDownRPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownRPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}