#include "Resident.h"

namespace
{
const float c_foodConsumptionTime = 10.0f;
const uint16 c_withoutFoodKillCount = 2;
}

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();

	m_aiController = Cast<AAIController>(GetController());

	m_worker = Cast<UWorker>(GetComponentByClass(UWorker::StaticClass()));
	check(m_worker != nullptr);
	m_treeCutter = Cast<UTreeCutter>(GetComponentByClass(UTreeCutter::StaticClass()));
	check(m_treeCutter != nullptr);
	m_builder = Cast<UBuilder>(GetComponentByClass(UBuilder::StaticClass()));
	check(m_builder != nullptr);
	m_gatherer = Cast<UGatherer>(GetComponentByClass(UGatherer::StaticClass()));
	check(m_gatherer != nullptr);

	m_worker->setEnabled(true);
	m_treeCutter->setEnabled(false);
	m_builder->setEnabled(false);
	m_gatherer->setEnabled(false);

	FActorSpawnParameters spawnParameters;
	FTransform transform(FVector(0.0f, 0.0f, 0.0f));
	m_infoText = (AInfoText*)GetWorld()->SpawnActor(m_infoTextClass, &transform, spawnParameters);
	check(m_infoText != nullptr);
	m_infoText->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	m_infoText->setText(FString("Worker"));
}


void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_foodConsumptionTimer += DeltaTime;
	if (m_foodConsumptionTimer > c_foodConsumptionTime)
	{
		AStorage* storage = findNearestStorageWithResource(AStorage::Resource::Food, 1);
		uint16 foodReceived = storage == nullptr ? 0 : storage->takeResource(AStorage::Resource::Food, 1);
		if (foodReceived == 0)
		{
			++m_timesWithoutFood;
			if (m_timesWithoutFood == c_withoutFoodKillCount)
			{
				Cast<AMyGameMode>(GetWorld()->GetAuthGameMode())->decreaseNumResidents();
				m_infoText->Destroy();
				Destroy();
			}
		}
		else
		{
			m_timesWithoutFood = 0;
		}
		m_foodConsumptionTimer = 0.0f;
	}
}

void AResident::setProfession(Profession profession)
{
	m_profession = profession;

	m_worker->setEnabled(profession == Profession::Worker);
	m_treeCutter->setEnabled(profession == Profession::TreeCutter);
	m_builder->setEnabled(profession == Profession::Builder);
	m_gatherer->setEnabled(profession == Profession::Gatherer);

	m_infoText->setText(professionToString[profession]);
}

AResident::Profession AResident::getProfession() const
{
	return m_profession;
}

AStorage* AResident::findNearestStorageWithSpace(uint16 spaceRequired)
{
	float smallestDistance = std::numeric_limits<float>::max();
	AStorage* nearestStorage = nullptr;
	for (TActorIterator<AStorage> iter(GetWorld()); iter; ++iter)
	{
		float distance = iter->GetDistanceTo(this);
		if (distance < smallestDistance && iter->getFreeSpace() >= spaceRequired && iter->getStatus() == ABuilding::Status::InGame)
		{
			smallestDistance = distance;
			nearestStorage = *iter;
		}
	}

	return nearestStorage;
}

AStorage* AResident::findNearestStorageWithResource(AStorage::Resource resource, uint16 amount)
{
	float smallestDistance = std::numeric_limits<float>::max();
	AStorage* nearestStorage = nullptr;
	for (TActorIterator<AStorage> iter(GetWorld()); iter; ++iter)
	{
		float distance = iter->GetDistanceTo(this);
		if (distance < smallestDistance && iter->getResourceAmount(resource) >= amount && iter->getStatus() == ABuilding::Status::InGame)
		{
			smallestDistance = distance;
			nearestStorage = *iter;
		}
	}

	return nearestStorage;
}

void AResident::moveToActor(AActor* actor)
{
	check(actor != nullptr);
	m_aiController->MoveToActor(actor);
}

void AResident::stopMovement()
{
	check(m_aiController != nullptr);
	m_aiController->StopMovement();
}

FVector AResident::getMoveDestination()
{
	check(m_aiController != nullptr);
	return m_aiController->GetImmediateMoveDestination();
}

EPathFollowingStatus::Type AResident::getMoveStatus()
{
	check(m_aiController != nullptr);
	return m_aiController->GetMoveStatus();
}