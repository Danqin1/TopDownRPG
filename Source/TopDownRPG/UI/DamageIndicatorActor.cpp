// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicatorActor.h"

#include "DamageIndicator.h"


// Sets default values
ADamageIndicatorActor::ADamageIndicatorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	SetRootComponent(DamageWidget);
}

// Called when the game starts or when spawned
void ADamageIndicatorActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADamageIndicatorActor::Tick(float DeltaTime)
{
	ShowTime += DeltaTime;
	SetActorLocation(GetActorLocation() +  FVector::UpVector * UpVelocity);
	if(ShowTime >= MaxShowTime)
	{
		Destroy();
	}
}

void ADamageIndicatorActor::Show(float Damage)
{
	if(auto* DamageIndicator = Cast<UDamageIndicator>(DamageWidget->GetWidget()))
	{
		DamageIndicator->DamageText->SetText(FText::FromString(FString::SanitizeFloat(Damage, 0)));
	}
}

