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

	if (m_readyAtStart)
	{
		setStatus(ABuilding::Status::InGame);
	}

	m_infoText->SetActorLocation(m_infoText->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));
}

void AStorage::addResource(AStorage::Resource resource, uint16 amount)
{
	check(m_gameMode != nullptr);
	AStorage::StaticClass();
	uint16& resourceAmount = resource == Resource::Wood ? m_woodAmount : m_foodAmount;
	resourceAmount += amount;
	m_gameMode->updateResources();
}

uint16 AStorage::getResourceAmount(AStorage::Resource resource)
{
	return resource == Resource::Wood ? m_woodAmount : m_foodAmount;;
}

uint16 AStorage::takeResource(AStorage::Resource resource, uint16 maxAmount)
{
	uint16& resourceAmount = resource == Resource::Wood ? m_woodAmount : m_foodAmount;
	uint16 takeAmount = std::min(maxAmount, resourceAmount);
	resourceAmount -= takeAmount;
	m_gameMode->updateResources();
	return takeAmount;
}

uint16 AStorage::getFreeSpace()
{
	return m_maxCapacity - m_woodAmount - m_foodAmount;
}

void AStorage::onBuildingReady()
{
	setMaterial(m_inGameMaterial);
}
