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

    CurrentTowerCount = GetTowerCount();

    TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (TankPlayer)
    {
        TankPlayerController = Cast<AToonTanksPlayerController>(TankPlayer->GetController());
        if (TankPlayerController)
        {
            TankPlayerController->SetEnabledInput(false);

            FTimerHandle GameStartTimerHandle;

            FTimerDelegate GameStartTimerDelegate = FTimerDelegate::CreateUObject(
                TankPlayerController, &AToonTanksPlayerController::SetEnabledInput, true);

            GetWorldTimerManager().SetTimer(GameStartTimerHandle, GameStartTimerDelegate, 3.0f, false);

            GameStart();
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

        GameOver(false);
        TankPlayer->HandleDestroy();
    }
    else if (ATower *Tower = Cast<ATower>(DeadActor))
    {
        if (--CurrentTowerCount <= 0)
        {
            GameOver(true);
        }

        Tower->HandleDestroy();
    }
}

int32 AToonTanksGameMode::GetTowerCount() const
{
    TArray<AActor *> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}