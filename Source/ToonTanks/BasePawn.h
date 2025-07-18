// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void RotateTurret(FVector LookAt);
	void Fire();

public:
	void HandleDestroy();

private:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *TurretMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	float TurretRotateSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClassType;

	class UHealth *Health;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase *DestroySound;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem *DestroyParticle;
};
