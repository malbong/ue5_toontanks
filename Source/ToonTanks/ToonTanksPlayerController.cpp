// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"

AToonTanksPlayerController::AToonTanksPlayerController()
{
}

void AToonTanksPlayerController::SetEnabledInput(bool bEnable)
{
    AActor *TankPlayer = GetPawn();
    if (!TankPlayer)
        return;

    if (bEnable)
    {
        TankPlayer->EnableInput(this);
    }
    else
    {
        TankPlayer->DisableInput(this);
    }

    bShowMouseCursor = bEnable;
}