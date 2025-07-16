// Fill out your copyright notice in the Description page of Project Settings.

#include "Health.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::TakenDamage);

	CurrentHP = MaxHP;
}

void UHealth::TakenDamage(AActor *DamagedActor,
						  float Damage,
						  const class UDamageType *DamageType,
						  class AController *InstigatedBy,
						  AActor *DamageCauser)
{
	if (CurrentHP <= 0.0f || Damage <= 0.0f || DamagedActor == nullptr)
		return;

	CurrentHP = (CurrentHP < Damage) ? 0.0f : CurrentHP - Damage;

	if (CurrentHP <= 0.0f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}