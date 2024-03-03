// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionComponent::SetupComponent()
{
	if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &UInteractionComponent::OnInteract);
	}

	if(auto* Character = Cast<ARPGCharacter>(GetOwner()))
	{
		PlayerCamera = Character->GetFollowCamera();
		PlayerHUD = Character->PlayerHUD;
		Character->OnStateChanged.AddDynamic(this, &UInteractionComponent::OnStateChanged);
	}
}

void UInteractionComponent::Dispose()
{
	if(auto* Character = Cast<ARPGCharacter>(GetOwner()))
	{
		Character->OnStateChanged.RemoveDynamic(this, &UInteractionComponent::OnStateChanged);
	}
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractionComponent::OnInteract()
{
	if(InteractionTarget.Get())
	{
		if(auto * Character = Cast<ARPGCharacter>(GetOwner()))
		{
			InteractionTarget.Get()->Interact(Character);
		}
	}
}

void UInteractionComponent::OnStateChanged(ECharacterState State)
{
	CurrentState = State;
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	if(PlayerCamera && CurrentState == Nothing && PlayerHUD)
	{
		FVector Start = PlayerCamera->GetComponentLocation();
		FVector End = Start + PlayerCamera->GetForwardVector() * InteractionMaxDistance;
		TArray<AActor*> ToIgnore;
		TArray<FHitResult> OutResults;
		ToIgnore.Add(GetOwner());
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

		bool hitted = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, 60,
											   ObjectTypes,
											   false,
											   ToIgnore,
											   EDrawDebugTrace::None, OutResults, true, FLinearColor::Red,
											   FLinearColor::Green, 3);

		if(hitted)
		{
			for (FHitResult OutResult : OutResults)
			{
				if(auto* Interactable = Cast<IInteractable>(OutResult.GetActor()))
				{
					InteractionTarget = Interactable;
					PlayerHUD->ShowInteraction(true);
					return;
				}
			}
		}
		InteractionTarget = nullptr;
		PlayerHUD->ShowInteraction(false);
	}
	else
	{
		InteractionTarget = nullptr;
		PlayerHUD->ShowInteraction(false);
	}
}

