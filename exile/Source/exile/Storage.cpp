#include "Storage.h"

#include <algorithm>

AStorage::AStorage()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStorage::BeginPlay()
{
	Super::BeginPlay();
	m_gameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
}

void AStorage::addWood(uint16 amount)
{
	check(m_gameMode != nullptr);
	AStorage::StaticClass();
	m_woodAmount += amount;
	m_gameMode->updateResources();
}

uint16 AStorage::getWoodAmount()
{
	return m_woodAmount;
}

uint16 AStorage::takeWood(uint16 maxAmount)
{
	uint16 takeAmount = std::min(maxAmount, m_woodAmount);
	m_woodAmount -= takeAmount;
	m_gameMode->updateResources();
	return takeAmount;
}

uint16 AStorage::getFreeSpace()
{
	return m_maxCapacity - m_woodAmount;
}

