// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDownRPG/Player/TopDownRPGPlayerController.h"


// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UAbilityComponent::SetupComponent()
{
	if(ATopDownRPGPlayerController* CharacterPC = Cast<ATopDownRPGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController = CharacterPC;
	}
}

void UAbilityComponent::Dispose()
{
}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	if(CurrentCastingIndicator && CurrentAbility)
	{
		if(PlayerController)
		{
			FHitResult Hit = PlayerController->GetLastMouseHit();
			FVector MouseDirection = Hit.Location - GetOwner()->GetActorLocation();
			MouseDirection.Normalize();
			
			switch (CurrentAbility->CastType)
			{
			case Direction:
				CurrentCastingIndicator->SetActorLocation(GetOwner()->GetActorLocation()
					+ MouseDirection * CurrentCastingIndicator->Length);
				CurrentCastingIndicator->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Hit.Location));
				break;
			case Target:
				CurrentCastingIndicator->SetActorLocation(Hit.Location);
				break;
			}
		}
	}
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(Ability1Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility1);
		Input->BindAction(Ability2Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility2);
		Input->BindAction(Ability3Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility3);
		Input->BindAction(Ability4Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility4);
		Input->BindAction(Ability5Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility5);
		Input->BindAction(Ability6Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility6);

		Input->BindAction(Ability1Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility1);
		Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility2);
		Input->BindAction(Ability3Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility3);
		Input->BindAction(Ability4Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility4);
		Input->BindAction(Ability5Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility5);
		Input->BindAction(Ability6Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility6);
	}
}

void UAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAbilityComponent::OnAbility1()
{
	TryUseAbility(Ability1);
}

void UAbilityComponent::OnAbility2()
{
	TryUseAbility(Ability2);
}

void UAbilityComponent::OnAbility3()
{
	TryUseAbility(Ability3);
}

void UAbilityComponent::OnAbility4()
{
	TryUseAbility(Ability4);
}

void UAbilityComponent::OnAbility5()
{
	TryUseAbility(Ability5);
}

void UAbilityComponent::OnAbility6()
{
	TryUseAbility(Ability6);
}

void UAbilityComponent::TryUseAbility(TSubclassOf<AAbility> Ability)
{
	if(CurrentAbility)
	{
		CastAbility(CurrentAbility);
	}
	else if(Ability)
	{
		SpawnAbility(Ability);
	}
}

void UAbilityComponent::SpawnAbility(TSubclassOf<AAbility> Ability)
{
	CurrentAbility = GetWorld()->SpawnActor<AAbility>(Ability);
	if(CurrentAbility)
	{
		switch (CurrentAbility->CastType)
		{
		case None:
			if(ACharacter* Character = Cast<ACharacter>(GetOwner()))
			{
				CurrentAbility->Activate(Character);
			}
			break;
		case Direction:
			CurrentCastingIndicator = GetWorld()->SpawnActor<ACaster>(DirectionalCasterClass, GetOwner()->GetTransform());
			break;
		case Target:
			CurrentCastingIndicator = GetWorld()->SpawnActor<ACaster>(TargetCasterClass, GetOwner()->GetTransform());
			break;
		}
	}
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, CurrentAbility ? "Ability Spawned" : "Ability spawn failed");
}

void UAbilityComponent::CastAbility(AAbility* Ability)
{
	if(CurrentAbility->CastType == None)
	{
		CurrentAbility = nullptr;
		return;
	}

	if(CurrentCastingIndicator)
	{
		GetWorld()->DestroyActor(CurrentCastingIndicator);
	}
	
	if(PlayerController)
	{
		FHitResult HitResult = PlayerController->GetLastMouseHit();
		
		if(ACharacter* Character =  Cast<ACharacter>(HitResult.GetActor()))
		{
			Ability->TargetCharacter = Character;
		}
		
		Ability->CastLocation = HitResult.Location;
		Ability->SetActorLocation(GetOwner()->GetActorLocation());
		Ability->Activate(PlayerController->GetCharacter());
		//clear current ability
		CurrentAbility = nullptr;
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Ability Casted");
	}
}

