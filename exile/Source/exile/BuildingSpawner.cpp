#include "BuildingSpawner.h"

ABuildingSpawner::ABuildingSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

