// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOONTANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void TakenDamage(AActor *DamagedActor,
					 float Damage,
					 const class UDamageType *DamageType,
					 class AController *InstigatedBy,
					 AActor *DamageCauser);

private:
	class AToonTanksGameMode *ToonTanksGameMode;

	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100.0f;

	float CurrentHP = 0.0f;
};
