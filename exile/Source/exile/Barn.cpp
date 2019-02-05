#include "Barn.h"

ABarn::ABarn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABarn::BeginPlay()
{
	Super::BeginPlay();
}

void ABarn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABarn::addWood(uint16 amount)
{
	ABarn::StaticClass();
	m_woodAmount += amount;
}

uint16 ABarn::getFreeSpace()
{
	return m_maxCapacity - m_woodAmount;
}

