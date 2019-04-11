#include "Storage.h"
#include "Classes/Components/SphereComponent.h"

#include <algorithm>

AStorage::AStorage()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStorage::BeginPlay()
{
	Super::BeginPlay();
	m_gameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());

	USphereComponent* sphereComponent = Cast<USphereComponent>(GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OnOverlapBegin);
	sphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABuilding::OnOverlapEnd);
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

void AStorage::setInGameMaterial()
{
	setMaterial(m_inGameMaterial);
}
