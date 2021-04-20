#include "TowerSpawner.h"

ATowerSpawner::ATowerSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATowerSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void ATowerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerSpawner::SpawnTower(TowerType Type, AActor* Tile)
{
	UE_LOG(LogTemp, Log, TEXT("Trying to spawn tower of type %d"), Type);
	const FTransform Transform(Tile->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor(GetTowerClass(Type), &Transform, SpawnParameters);
	UE_LOG(LogTemp, Log, TEXT("Tower Spawned"));

}

UClass* ATowerSpawner::GetTowerClass(TowerType Type)
{
	if (Type == Tower_Gun)
	{
		return GunTower.Get();
	}
	else if (Type == Tower_Splash)
	{
		return SplashTower.Get();
	}
	UE_LOG(LogTemp, Log, TEXT("Incorrect tower type, retuning gun tower"));

	return GunTower.Get();
}