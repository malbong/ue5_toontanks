// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent,
			   AActor *OtherActor,
			   UPrimitiveComponent *OtherComp,
			   FVector NormalImpulse,
			   const FHitResult &HitResult);

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem *HitParticle;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent *TrailParticle;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase *ProjectileSound;
};
