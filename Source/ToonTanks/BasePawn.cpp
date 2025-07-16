// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAt)
{
	FVector ToTargetLocation = LookAt - TurretMesh->GetComponentLocation();
	FRotator ToTargetRotation = FRotator(0, ToTargetLocation.Rotation().Yaw, 0);

	FRotator DeltaRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		ToTargetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		TurretRotateSpeed);

	TurretMesh->SetWorldRotation(DeltaRotation, true);
}

void ABasePawn::Fire()
{
	AProjectile *SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClassType, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());

	if (SpawnedProjectile)
	{
		SpawnedProjectile->SetOwner(this);
		SpawnedProjectile->SetInstigator(this);
	}
}