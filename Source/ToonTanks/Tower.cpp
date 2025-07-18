// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckInFireRangeAndFire, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayer && InFireRange())
    {
        RotateTurret(TankPlayer->GetActorLocation());
    }
}

void ATower::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATower::HandleDestroy()
{
    Super::HandleDestroy();

    Destroy();
}

bool ATower::InFireRange() const
{
    if (TankPlayer && TankPlayer->IsAlive())
    {
        float Distance = FVector::Distance(GetActorLocation(), TankPlayer->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }

    return false;
}

void ATower::CheckInFireRangeAndFire()
{
    if (InFireRange())
    {
        Fire();
    }
}