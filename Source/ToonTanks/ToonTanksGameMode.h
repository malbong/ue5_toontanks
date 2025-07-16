// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToonTanksGameMode();

	void ActorDied(AActor *DeadActor);

	UFUNCTION(BlueprintImplementableEvent, meta = (AllowAccessPrivate = "true"))
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent, meta = (AllowAccessPrivate = "true"))
	void GameOver(bool bWon);

protected:
	virtual void BeginPlay() override;

private:
	class ATank *TankPlayer;
	class AToonTanksPlayerController *TankPlayerController;

	int32 CurrentTowerCount = 0;

	int32 GetTowerCount() const;
};
