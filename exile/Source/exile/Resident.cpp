#include "Resident.h"


AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();

	m_worker = Cast<UWorker>(GetComponentByClass(UWorker::StaticClass()));
	check(m_worker != nullptr);
	m_treeCutter = Cast<UTreeCutter>(GetComponentByClass(UTreeCutter::StaticClass()));
	check(m_treeCutter != nullptr);
	m_builder = Cast<UBuilder>(GetComponentByClass(UBuilder::StaticClass()));
	check(m_builder != nullptr);

	m_worker->SetActive(false);
	m_treeCutter->SetActive(false);
	m_builder->SetActive(false);

	m_aiController = Cast<AAIController>(GetController());
}


void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_destination = getMoveDestination();
}

void AResident::setProfession(Profession profession)
{
	m_worker->Deactivate();
	m_treeCutter->Deactivate();
	m_builder->Deactivate();

	if (profession == Profession::Worker)
	{
		m_worker->Activate();
	}
	else if (profession == Profession::TreeCutter)
	{
		m_treeCutter->Activate();
	}
	else if (profession == Profession::Builder)
	{
		m_builder->Activate();
	}
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
	check(actor != nullptr);
	m_aiController->MoveToActor(actor);
}

void AResident::stopMovement()
{
	m_aiController->StopMovement();
}

FVector AResident::getMoveDestination()
{
	return m_aiController->GetImmediateMoveDestination();
}

