#pragma once

#include "Tower.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawner.generated.h"

UENUM(BlueprintType)
enum TowerType
{
	Tower_Gun,
	Tower_Splash
};

UCLASS()
class TD_API ATowerSpawner : public AActor
{
	GENERATED_BODY()

public:
	ATowerSpawner();
	virtual void Tick(float DeltaTime) override;
	void SpawnTower(TowerType Type, AActor* Tile);

protected:
	virtual void BeginPlay() override;

private:
	UClass* GetTowerClass(TowerType Type);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATower> GunTower;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATower> SplashTower;
};
