#include "House.h"

AHouse::AHouse()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
}

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

