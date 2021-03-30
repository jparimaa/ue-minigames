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
	AEnemySpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> EnemyClass;

	std::chrono::time_point<std::chrono::system_clock> LastSpawnTime;
};
