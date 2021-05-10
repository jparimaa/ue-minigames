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
	bool UpdateSpawnIndices();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> LightEnemyClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> HeavyEnemyClass;

	FTransform SpawnPoint;
	FActorSpawnParameters SpawnParameters;

	TArray<TArray<FPack>> EnemyWaves;

	std::chrono::time_point<std::chrono::system_clock> LastSpawnTime;
	std::chrono::time_point<std::chrono::system_clock> WaveEndTime;
	int EnemyIndex = 0;
	int PackIndex = 0;
	int WaveIndex = 0;
	bool Running = true;
};
