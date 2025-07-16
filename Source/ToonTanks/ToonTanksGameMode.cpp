// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

AToonTanksGameMode::AToonTanksGameMode()
    : TankPlayer(nullptr), TankPlayerController(nullptr)
{
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (TankPlayer)
    {
        TankPlayerController = Cast<AToonTanksPlayerController>(TankPlayer->GetController());
        if (TankPlayerController)
        {
            TankPlayerController->SetEnabledInput(true);
        }
    }
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == nullptr)
        return;

    if (DeadActor == TankPlayer)
    {
        if (TankPlayerController)
        {
            TankPlayerController->SetEnabledInput(false);
        }

        TankPlayer->HandleDestroy();
    }
    else if (ATower *Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestroy();
    }
}