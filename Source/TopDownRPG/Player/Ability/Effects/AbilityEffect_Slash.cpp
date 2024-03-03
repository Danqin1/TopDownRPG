// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityEffect_Slash.h"

#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TopDownRPG/Enemy/EnemyCharacter.h"
#include "TopDownRPG/Interfaces/Enemy.h"
#include "TopDownRPG/Player/RPGCharacter.h"


// Sets default values
AAbilityEffect_Slash::AAbilityEffect_Slash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbilityEffect_Slash::BeginPlay()
{
	Super::BeginPlay();
}

void AAbilityEffect_Slash::Activate(ACharacter* Caster)
{
	if(Caster && SlashAnimation)
	{
		if(ARPGCharacter* CasterCharacter = Cast<ARPGCharacter>(Caster))
		{
			TArray<FHitResult> OutResults;
			FVector Start = Caster->GetActorLocation();
			FVector End = Start + Caster->GetActorForwardVector() * TraceLength;
			TArray<AActor*> ToIgnore;
			ToIgnore.Add(Caster);
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

			UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, 60,
												   ObjectTypes,
												   false,
												   ToIgnore,
												   EDrawDebugTrace::ForDuration, OutResults, true, FLinearColor::Red,
												   FLinearColor::Green, 3);

			for (FHitResult OutResult : OutResults)
			{
				if(IEnemy* Enemy = Cast<IEnemy>(OutResult.GetActor()))
				{
					Enemy->OnHitReaction(SlashReactionAnimation);
					Caster->GetMovementComponent()->StopMovementImmediately();
					Caster->PlayAnimMontage(SlashAnimation);

					CasterCharacter->CombatComponent->ModifyDamage(Damage);
			
					FTimerHandle TimerHandle;
					float AnimTime = SkillDuration;

					FTimerHandle AttachHandle;
					float AttachTime = FVector::Dist(OutResult.GetActor() -> GetActorLocation(), CasterCharacter->GetActorLocation()) / 500 * AttachDelay;

					GetWorld()->GetTimerManager().SetTimer(AttachHandle, [this, CasterCharacter, OutResult]()
					{
						if(CasterCharacter)
						{
							if(auto* enemy = Cast<AEnemyCharacter>(OutResult.GetActor()))
							{
								enemy->SetAirborne(true);
								enemy->GetCharacterMovement()->StopMovementImmediately();
								enemy->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
							}
							CasterCharacter->GetMesh()->GetSocketByName(AttachSocketName)->AttachActor(OutResult.GetActor(), CasterCharacter->GetMesh());
						}
					}, AttachTime, false, AttachTime);

					FTimerHandle EndHitHandle;
					float EndHitTime = AttachTime + AirHitsDuration;

					GetWorld()->GetTimerManager().SetTimer(EndHitHandle, [this, CasterCharacter, OutResult]()
					{
						if(CasterCharacter)
						{
							if(auto* enemy = Cast<AEnemyCharacter>(OutResult.GetActor()))
							{
								enemy->SetAirborne(false);
								enemy->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
							}
							OutResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
						}
					}, EndHitTime, false, EndHitTime);
					
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, CasterCharacter, OutResult]()
					{
						if(CasterCharacter)
						{
							CasterCharacter->CombatComponent->ClearDamageModifier();
						}
						
						Destroy();
					}, AnimTime, false, AnimTime);
					
					return;
				}
			}
		}
	}
}
