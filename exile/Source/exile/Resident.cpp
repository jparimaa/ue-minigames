#include "Resident.h"

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* AResident::findNearestBarnWithSpace(uint16 spaceRequired)
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, ABarn::StaticClass());
	float smallestDistance = std::numeric_limits<float>::max();
	AActor* nearestBarn = nullptr;
	for (AActor* actor : overlappingActors)
	{
		ABarn* barn = Cast<ABarn>(actor);
		float distance = actor->GetDistanceTo(this);
		if (distance < smallestDistance && barn->getFreeSpace() >= spaceRequired)
		{
			smallestDistance = distance;
			nearestBarn = actor;
		}
	}
	return nearestBarn;
}

FVector AResident::getDirectionTo(AActor* actor)
{
	FVector direction;
	if (actor != nullptr)
	{
		direction = actor->GetActorLocation() - GetActorLocation();
		direction.Normalize();
	}
	return direction;
}

void AResident::move(FVector direction)
{
	FVector newLocation = GetActorLocation();
	newLocation += direction * m_speed;
	SetActorLocation(newLocation);
}

void AResident::BeginPlay()
{
	Super::BeginPlay();
}
