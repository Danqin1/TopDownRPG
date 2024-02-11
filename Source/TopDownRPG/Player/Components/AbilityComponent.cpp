// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Player/TopDownRPGPlayerController.h"


// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAbilityComponent::SetupComponent()
{
}

void UAbilityComponent::Dispose()
{
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

		Input->BindAction(Ability1Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility1);
		Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility2);
		Input->BindAction(Ability3Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility3);
		Input->BindAction(Ability4Action, ETriggerEvent::Completed, this, &UAbilityComponent::OnAbility4);
	}
}

void UAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAbilityComponent::OnAbility1()
{
	if(CurrentAbility)
	{
		CastAbility(CurrentAbility);
	}
	else
	{
		SpawnAbility(Ability1);
	}
}

void UAbilityComponent::OnAbility2()
{
	if(CurrentAbility)
	{
		CastAbility(CurrentAbility);
	}
	else
	{
		SpawnAbility(Ability2);
	}
}

void UAbilityComponent::OnAbility3()
{
	if(CurrentAbility)
	{
		CastAbility(CurrentAbility);
	}
	else
	{
		SpawnAbility(Ability3);
	}
}

void UAbilityComponent::OnAbility4()
{
	if(CurrentAbility)
	{
		CastAbility(CurrentAbility);
	}
	else
	{
		SpawnAbility(Ability4);
	}
}

void UAbilityComponent::SpawnAbility(TSubclassOf<AAbility> Ability)
{
	if(!Ability) return;
	CurrentAbility = GetWorld()->SpawnActor<AAbility>(Ability);
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, CurrentAbility ? "Ability Spawned" : "Ability spawn failed");
}

void UAbilityComponent::CastAbility(AAbility* Ability)
{
	if(!Ability) return;
	
	if(ATopDownRPGPlayerController* CharacterPC = Cast<ATopDownRPGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		FHitResult HitResult;
		if(CharacterPC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			if(ACharacter* Character =  Cast<ACharacter>(HitResult.GetActor()))
			{
				Ability->TargetCharacter = Character;
			}
			Ability->CastLocation = HitResult.Location;
		}
		Ability->Activate(CharacterPC->GetCharacter());
		//clear current ability
		CurrentAbility = nullptr;
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Ability Casted");
	}
}

