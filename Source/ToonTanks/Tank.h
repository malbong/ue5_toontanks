// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void HandleDestroy();

	inline bool IsAlive() const { return bAlive; }

private:
	void MoveForward(float Value);
	void Turn(float Value);

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent *SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent *Camera;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 800.0f;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate = 90.0f;

	class APlayerController *PlayerController;

	bool bAlive = false;
};
