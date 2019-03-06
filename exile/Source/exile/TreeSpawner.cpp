#include "TreeSpawner.h"
#include "Constants.h"

#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

const float c_spawnTime = 3.0f;

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
		float x = FMath::FRandRange(-c_worldSize, c_worldSize);
		float y = FMath::FRandRange(-c_worldSize, c_worldSize);
		FVector location(x, y, 0.0f);
		FTransform transform(location);
		FActorSpawnParameters spawnParameters;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ATree* SpawnedActor1 = (ATree*)GetWorld()->SpawnActor(m_classToSpawn, &transform, spawnParameters);
		m_counter = 0.0f;
	}
}

