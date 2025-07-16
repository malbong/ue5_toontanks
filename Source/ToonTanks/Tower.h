// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void HandleDestroy();

	class ATank *TankPlayer;

	UPROPERTY(EditDefaultsOnly)
	float FireRange = 700.0f;

	UPROPERTY(EditDefaultsOnly)
	float FireRate = 2.0f;

	FTimerHandle FireTimerHandle;

	bool InFireRange() const;

	void CheckInFireRangeAndFire();
};
