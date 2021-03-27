#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameData.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.generated.h"

UCLASS()
class FPS_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	GameData* GetGameData() { return &MyGameData; }

	void GameOver();

private:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidget);

	std::chrono::time_point<std::chrono::system_clock> LastSpawnTime;
	GameData MyGameData;
	bool IsGameOver = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> RestartWidgetClass;

	UUserWidget* CurrentWidget;
};
