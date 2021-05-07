#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TD_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	enum class EEnemyType
	{
		Light,
		Heavy
	};

	struct FPack
	{
		EEnemyType Type;
		int Count;
	};

	AEnemySpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void LoadEnemySpawnData();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere)
		int MaxSpawnCount = 10;

	UPROPERTY(VisibleAnywhere)
		int SpawnCount = 0;

	UPROPERTY(EditAnywhere)
		int SpawnIntervalMS = 1000;

	TArray<TArray<FPack>> EnemyWaves;

	std::chrono::time_point<std::chrono::system_clock> LastSpawnTime;
};
