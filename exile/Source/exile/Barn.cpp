#include "Barn.h"

ABarn::ABarn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABarn::BeginPlay()
{
	Super::BeginPlay();
	m_gameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
}

void ABarn::addWood(uint16 amount)
{
	ABarn::StaticClass();
	m_woodAmount += amount;
	if (m_gameMode != nullptr)
	{
		m_gameMode->updateResources();
	}
}

uint16 ABarn::getWoodAmount()
{
	return m_woodAmount;
}

uint16 ABarn::getFreeSpace()
{
	return m_maxCapacity - m_woodAmount;
}

