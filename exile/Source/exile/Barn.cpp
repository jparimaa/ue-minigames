#include "Barn.h"

#include <algorithm>

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
	check(m_gameMode != nullptr);
	ABarn::StaticClass();
	m_woodAmount += amount;
	m_gameMode->updateResources();
}

uint16 ABarn::getWoodAmount()
{
	return m_woodAmount;
}

uint16 ABarn::takeWood(uint16 maxAmount)
{
	uint16 takeAmount = std::min(maxAmount, m_woodAmount);
	m_woodAmount -= takeAmount;
	m_gameMode->updateResources();
	return takeAmount;
}

uint16 ABarn::getFreeSpace()
{
	return m_maxCapacity - m_woodAmount;
}

