// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDownRPG/DevDebug.h"
#include "TopDownRPG/Player/RPGCharacter.h"
#include "TopDownRPG/Player/RPGPlayerController.h"


// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	CurrentAbilities.SetNum(MAX_ABILITIES_COUNT, false);
}

void UAbilityComponent::SetupComponent()
{
	if(ARPGPlayerController* CharacterPC = Cast<ARPGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController = CharacterPC;
	}

	if(ARPGCharacter* Player = Cast<ARPGCharacter>(GetOwner()))
	{
		PlayerHUD = Player->PlayerHUD;
		check(PlayerHUD);
	}
	
	//Initial setup abiities for tests
	ChangeAbilityOnIndex(0, Ability1);
	ChangeAbilityOnIndex(1, Ability2);
	ChangeAbilityOnIndex(2, Ability3);
	ChangeAbilityOnIndex(3, Ability4);
	ChangeAbilityOnIndex(4, Ability5);
	ChangeAbilityOnIndex(5, Ability6);
}

void UAbilityComponent::Dispose()
{
}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	/*if(CurrentCastingIndicator && CurrentCastingAbility)
	{
		if(PlayerController)
		{
			FHitResult Hit = PlayerController->GetLastMouseHit();
			FVector MouseDirection = Hit.Location - GetOwner()->GetActorLocation();
			MouseDirection.Normalize();
			
			switch (CurrentCastingAbility->CastType)
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
	}*/
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	/*if(UEnhancedInputComponent* Input = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		Input->BindAction(Ability1Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility1);
		Input->BindAction(Ability2Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility2);
		Input->BindAction(Ability3Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility3);
		Input->BindAction(Ability4Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility4);
		Input->BindAction(Ability5Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility5);
		Input->BindAction(Ability6Action, ETriggerEvent::Started, this, &UAbilityComponent::OnAbility6);

		Input->BindAction(Ability1Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
		Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
		Input->BindAction(Ability3Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
		Input->BindAction(Ability4Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
		Input->BindAction(Ability5Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
		Input->BindAction(Ability6Action, ETriggerEvent::Completed, this, &UAbilityComponent::CastAbility);
	}*/
}

void UAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAbilityComponent::OnAbility1()
{
	TryUseAbility(CurrentAbilities[0]);
}

void UAbilityComponent::OnAbility2()
{
	TryUseAbility(CurrentAbilities[1]);
}

void UAbilityComponent::OnAbility3()
{
	TryUseAbility(CurrentAbilities[2]);
}

void UAbilityComponent::OnAbility4()
{
	TryUseAbility(CurrentAbilities[3]);
}

void UAbilityComponent::OnAbility5()
{
	TryUseAbility(CurrentAbilities[4]);
}

void UAbilityComponent::OnAbility6()
{
	TryUseAbility(CurrentAbilities[5]);
}

void UAbilityComponent::TryUseAbility(AAbility* Ability)
{
	if(Ability && Ability->CanUseAbility())
	{
		InitAbility(Ability);
	}
}

void UAbilityComponent::InitAbility(AAbility* Ability)
{
	CurrentCastingAbility = Ability;
	CurrentCastingAbility->TargetCharacter = nullptr;
	
	if(CurrentCastingAbility)
	{
		switch (CurrentCastingAbility->CastType)
		{
		case None:
			CurrentCastingAbility->Activate(PlayerController->GetCharacter());
			break;
		case Direction:
			CurrentCastingIndicator = GetWorld()->SpawnActor<ACaster>(DirectionalCasterClass, GetOwner()->GetTransform());
			break;
		case Target:
			CurrentCastingIndicator = GetWorld()->SpawnActor<ACaster>(TargetCasterClass, GetOwner()->GetTransform());
			break;
		}
	}
}

void UAbilityComponent::CastAbility()
{
	if(!CurrentCastingAbility || CurrentCastingAbility->CastType == None)
	{
		CurrentCastingAbility = nullptr;
		return;
	}

	if(CurrentCastingIndicator)
	{
		GetWorld()->DestroyActor(CurrentCastingIndicator);
	}
	
	if(PlayerController)
	{
		//FHitResult HitResult = PlayerController->GetLastMouseHit();
		
		/*if(ACharacter* Character =  Cast<ACharacter>(HitResult.GetActor()))
		{
			CurrentCastingAbility->TargetCharacter = Character;
		}*/
		
		CurrentCastingAbility->CastLocation = GetOwner()->GetActorLocation();//HitResult.Location;
		CurrentCastingAbility->SetActorLocation(GetOwner()->GetActorLocation());
		CurrentCastingAbility->Activate(PlayerController->GetCharacter());
		
		CurrentCastingAbility = nullptr;
	}
}

void UAbilityComponent::ChangeAbilityOnIndex(int Index, TSubclassOf<AAbility> AbilityClass)
{
	if(Index <  MAX_ABILITIES_COUNT)
	{
		if(CurrentAbilities[Index])
		{
			GetWorld()->DestroyActor(CurrentAbilities[Index]);
		}

		if(AbilityClass)
		{
			CurrentAbilities[Index] = GetWorld()->SpawnActor<AAbility>(AbilityClass);
			if(CurrentAbilities[Index] && PlayerHUD)
			{
				CurrentAbilities[Index]->SetUISlot(PlayerHUD->GetUISlot(Index));
				
				if(ACharacter* Character = Cast<ACharacter>(GetOwner()))
				{
					CurrentAbilities[Index]->CasterCharacter = Character;
				}
				else
				{
					DevDebug::OnScreenLog("Cant set up Caster");
				}
			}
			else
			{
				DevDebug::OnScreenLog("Cant set UI slot", FColor::Red, 5);
			}
		}
		else
		{
			DevDebug::OnScreenLog("Ability not set up: " + FString::SanitizeFloat(Index));
		}
	}
	else
	{
		DevDebug::OnScreenLog("Index higher than abilities array");
	}
}

