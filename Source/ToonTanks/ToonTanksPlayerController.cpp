// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"

AToonTanksPlayerController::AToonTanksPlayerController()
{
}

void AToonTanksPlayerController::BeginPlay()
{
    TankPlayer = GetPawn();
}

void AToonTanksPlayerController::SetEnabledInput(bool bEnable)
{
    if (bEnable)
    {
        if (TankPlayer)
        {
            TankPlayer->EnableInput(this);
        }
    }
    else
    {
        if (TankPlayer)
        {
            TankPlayer->DisableInput(this);
        }
    }

    bShowMouseCursor = bEnable;
}