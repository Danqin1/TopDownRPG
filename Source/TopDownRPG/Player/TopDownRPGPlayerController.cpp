// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownRPGPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownRPGCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownRPG/Interfaces/IDamageable.h"
#include "TopDownRPG/Interfaces/Interactable.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATopDownRPGPlayerController::ATopDownRPGPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATopDownRPGPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void ATopDownRPGPlayerController::Tick(float DeltaSeconds)
{
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if(bHitSuccessful)
	{
		if(auto* Enemy = Cast<IIDamageable>(Hit.GetActor()))
		{
			CurrentMouseCursor = EMouseCursor::Crosshairs;
		}
		else if(auto* Interactable = Cast<IInteractable>(Hit.GetActor()))
		{
			CurrentMouseCursor = EMouseCursor::GrabHand;
		}
		else
		{
			CurrentMouseCursor = EMouseCursor::Default;
		}
	}
	
	if(CurrentInteractionActor)
	{
		if(IInteractable* Interactable = Cast<IInteractable>(CurrentInteractionActor))
		{
			if(FVector::Dist(CurrentInteractionActor->GetActorLocation(), GetCharacter()->GetActorLocation()) < CurrentInteractionMaxRange)
			{
				Interactable->Interact(Cast<ATopDownRPGCharacter>(GetCharacter()));
				CurrentInteractionActor = nullptr;
			}
			SetAutoAttack(false);
		}
		else if(IIDamageable* Enemy = Cast<IIDamageable>(CurrentInteractionActor))
		{
			FVector Dir = CurrentInteractionActor->GetActorLocation() - GetCharacter()->GetActorLocation();
			float Dot = FVector::DotProduct(Dir, GetCharacter()->GetActorForwardVector());
			
			if(FVector::Dist(CurrentInteractionActor->GetActorLocation(), GetCharacter()->GetActorLocation()) < CurrentInteractionMaxRange
				&& Dot > .6)
			{
				SetAutoAttack(true);
			}
			else
			{
				SetAutoAttack(false);
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CurrentInteractionActor->GetActorLocation());
			}
		}
	}
	else
	{
		SetAutoAttack(false);
	}
	Super::Tick(DeltaSeconds);
}

void ATopDownRPGPlayerController::SetInteractWith(AActor* Actor, float MaxRange)
{
	CurrentInteractionActor = Actor;
	CurrentInteractionMaxRange = MaxRange;
}

void ATopDownRPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATopDownRPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATopDownRPGPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATopDownRPGPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATopDownRPGPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATopDownRPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATopDownRPGPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATopDownRPGPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATopDownRPGPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &ATopDownRPGPlayerController::OnZoomInOut);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATopDownRPGPlayerController::OnInputStarted()
{
	if(auto* Enemy = Cast<IIDamageable>(Hit.GetActor()))
	{
		CurrentInteractionActor = Hit.GetActor();
		CurrentInteractionMaxRange = Settings->MeleeAttackRange; // change later depends on weapon?
	}
	else if(auto* Interactable = Cast<IInteractable>(Hit.GetActor()))
	{
		Interactable->OnClicked();
	}
	else
	{
		CurrentInteractionActor = nullptr;
	}
	StopMovement();
}

// Triggered every frame when the input is held down
void ATopDownRPGPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	if(Hit.IsValidBlockingHit())
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATopDownRPGPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATopDownRPGPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATopDownRPGPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATopDownRPGPlayerController::OnZoomInOut(const FInputActionValue& Value)
{
	if(ATopDownRPGCharacter* TopDownCharacter = Cast<ATopDownRPGCharacter>(GetCharacter()))
	{
		const float CurrentZoom = TopDownCharacter->GetCameraBoom()->TargetArmLength;
		TopDownCharacter->GetCameraBoom()->TargetArmLength = FMath::Clamp(CurrentZoom + Value.Get<float>() * Settings->ZoomSpeed, Settings->MinCameraDistance, Settings->MaxCameraDistance);
	}
}

void ATopDownRPGPlayerController::SetAutoAttack(bool enabled)
{
	if(ATopDownRPGCharacter* RPGPlayer = Cast<ATopDownRPGCharacter>(GetCharacter()))
	{
		RPGPlayer->SetAutoAttack(enabled);
	}
}

FHitResult ATopDownRPGPlayerController::GetLastMouseHit()
{
	return Hit;
}
