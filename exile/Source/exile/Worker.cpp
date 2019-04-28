#include "Worker.h"
#include "Resident.h"

#include <algorithm>

namespace
{
uint16 c_maxAmountWoodCarrying = 50;
}

UWorker::UWorker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorker::BeginPlay()
{
	Super::BeginPlay();

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UWorker::OnOverlapBegin);
}

void UWorker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}

	if (m_status == Status::WaitingForBuilding && m_buildingToCarryWoodTo == nullptr)
	{
		m_buildingToCarryWoodTo = getBuildingToCarryWood();
		if (m_buildingToCarryWoodTo != nullptr)
		{
			m_status = Status::WaitingForWood;
		}
	}

	if (m_status == Status::WaitingForWood && m_storageToGetWoodFrom == nullptr)
	{
		check(m_buildingToCarryWoodTo != nullptr);
		m_storageToGetWoodFrom = getStorageWithWood();
		if (m_storageToGetWoodFrom != nullptr)
		{
			m_status = Status::GettingWoodFromStorage;
			m_owner->moveToActor(m_storageToGetWoodFrom);
		}
	}

	if (m_status == Status::GettingWoodFromStorage)
	{
		check(m_buildingToCarryWoodTo != nullptr);
		check(m_storageToGetWoodFrom != nullptr);
		AStorage* newStorage = getStorageWithWood();
		if (newStorage != m_storageToGetWoodFrom)
		{
			m_owner->moveToActor(m_storageToGetWoodFrom);
		}
		else if (newStorage == nullptr)
		{
			m_owner->stopMovement();
			m_status = Status::WaitingForWood;
		}
		m_storageToGetWoodFrom = newStorage;
	}

	if (m_status == Status::CarryingWoodToBuilding)
	{
		ABuilding* newBuilding = getBuildingToCarryWood();
		if (newBuilding != m_buildingToCarryWoodTo)
		{
			m_owner->moveToActor(m_buildingToCarryWoodTo);
		}
		else if (newBuilding == nullptr)
		{
			m_status = Status::WaitingForBuilding;
		}
		m_buildingToCarryWoodTo = newBuilding;
	}
}

ABuilding* UWorker::getBuildingToCarryWood()
{
	return m_owner->findNearestActor<ABuilding>([](ABuilding* building) {
		return building->getStatus() == ABuilding::Status::GettingWood && building->getWoodRequiredForConstruction() > 0;
	});
}

AStorage* UWorker::getStorageWithWood()
{
	return m_owner->findNearestActor<AStorage>([](AStorage* storage) { return storage->getResourceAmount(AStorage::Resource::Wood) > 0; });
}

void UWorker::setEnabled(bool status)
{
	m_enabled = status;
	if (!m_enabled)
	{
		m_status = Status::WaitingForBuilding;
		m_storageToGetWoodFrom = nullptr;
		m_buildingToCarryWoodTo = nullptr;
		m_amountWoodCarrying = 0;
	}
}

void UWorker::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (m_status == Status::GettingWoodFromStorage && OtherActor == m_storageToGetWoodFrom)
	{
		m_owner->stopMovement();

		ABuilding* newBuilding = getBuildingToCarryWood();

		if (newBuilding != nullptr)
		{
			m_amountWoodCarrying = m_storageToGetWoodFrom->takeResource(AStorage::Resource::Wood, c_maxAmountWoodCarrying - m_amountWoodCarrying);
			m_status = Status::CarryingWoodToBuilding;
			m_buildingToCarryWoodTo = newBuilding;
			m_owner->moveToActor(m_buildingToCarryWoodTo);
		}
	}

	if (m_status == Status::CarryingWoodToBuilding && OtherActor == m_buildingToCarryWoodTo)
	{
		m_owner->stopMovement();
		uint16 woodRequired = m_buildingToCarryWoodTo->getWoodRequiredForConstruction();
		uint16 amountWoodToAdd = std::min(woodRequired, m_amountWoodCarrying);
		m_buildingToCarryWoodTo->addWoodForConstruction(amountWoodToAdd);
		m_amountWoodCarrying -= amountWoodToAdd;
		m_storageToGetWoodFrom = nullptr;
		m_buildingToCarryWoodTo = nullptr;
		m_status = Status::WaitingForBuilding;
	}
}