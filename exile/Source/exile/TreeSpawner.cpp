#include "TreeSpawner.h"

const float c_spawnTime = 5.0f;

ATreeSpawner::ATreeSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
	check(m_classToSpawn);
}

void ATreeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_counter += DeltaTime;
	if (m_counter > c_spawnTime)
	{
		float multiplier = static_cast<float>(m_numTreesSpawned);
		FVector location(multiplier * 100.0f, 0.0f, 170.0f);
		ATree* SpawnedActor1 = (ATree*)GetWorld()->SpawnActor(m_classToSpawn, &location);
		m_counter = 0.0f;
		++m_numTreesSpawned;
	}
}

