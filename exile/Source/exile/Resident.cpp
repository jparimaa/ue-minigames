#include "Resident.h"

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();
	m_aiController = Cast<AAIController>(GetController());

	moveToActor(findNearestBarnWithSpace(0));
}


void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABarn* AResident::findNearestBarnWithSpace(uint16 spaceRequired)
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, ABarn::StaticClass());
	float smallestDistance = std::numeric_limits<float>::max();
	ABarn* nearestBarn = nullptr;
	for (AActor* actor : overlappingActors)
	{
		ABarn* barn = Cast<ABarn>(actor);
		float distance = actor->GetDistanceTo(this);
		if (distance < smallestDistance && barn->getFreeSpace() >= spaceRequired)
		{
			smallestDistance = distance;
			nearestBarn = Cast<ABarn>(actor);
		}
	}
	return nearestBarn;
}

void AResident::moveToActor(AActor* actor)
{
	if (actor != nullptr)
	{
		m_aiController->MoveToActor(actor);
	}
}

