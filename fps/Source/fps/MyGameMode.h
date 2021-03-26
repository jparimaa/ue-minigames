// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameData.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 *
 */
UCLASS()
class FPS_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> EnemyClass;

	GameData* GetGameData() { return &MyGameData; }

	void GameOver();

private:
	std::chrono::time_point<std::chrono::system_clock> LastSpawnTime;
	GameData MyGameData;
	bool IsGameOver = false;
};
