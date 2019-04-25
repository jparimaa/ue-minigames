#include "ResourceSpawner.h"
#include "Constants.h"

#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

AResourceSpawner::AResourceSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	m_spawnSettings.Add({ 0.0f, 15.0f, &m_treeClass });
	m_spawnSettings.Add({ 0.0f, 15.0f, &m_gatherableClass });
}

void AResourceSpawner::BeginPlay()
{
	Super::BeginPlay();
	check(m_treeClass);
	check(m_gatherableClass);
}

void AResourceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (SpawnSettings& spawnSettings : m_spawnSettings)
	{
		spawnSettings.counter += DeltaTime;
		if (spawnSettings.counter > spawnSettings.spawnTime)
		{
			float x = FMath::FRandRange(-c_worldSize, c_worldSize);
			float y = FMath::FRandRange(-c_worldSize, c_worldSize);
			FVector location(x, y, 0.0f);
			FTransform transform(location);
			FActorSpawnParameters spawnParameters;
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			GetWorld()->SpawnActor(*spawnSettings.actorClass, &transform, spawnParameters);
			spawnSettings.counter = 0.0f;
		}
	}
}


