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

	if (m_status == Status::WaitingForWood && m_barnToGetWoodFrom == nullptr)
	{
		check(m_buildingToCarryWoodTo != nullptr);
		m_barnToGetWoodFrom = getBarnWithWood();
		if (m_barnToGetWoodFrom != nullptr)
		{
			m_status = Status::GettingWoodFromBarn;
			m_owner->moveToActor(m_barnToGetWoodFrom);
		}
	}

	if (m_status == Status::GettingWoodFromBarn)
	{
		check(m_buildingToCarryWoodTo != nullptr);
		check(m_barnToGetWoodFrom != nullptr);
		ABarn* newBarn = getBarnWithWood();
		if (newBarn != m_barnToGetWoodFrom)
		{
			m_owner->moveToActor(m_barnToGetWoodFrom);
		}
		else if (newBarn == nullptr)
		{
			m_status = Status::WaitingForWood;
		}
		m_barnToGetWoodFrom = newBarn;
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
		return building->getStatus() == ABuilding::Status::Constructing && building->getWoodRequiredForConstruction() > 0;
	});
}

ABarn* UWorker::getBarnWithWood()
{
	return m_owner->findNearestActor<ABarn>([](ABarn* barn) { return barn->getWoodAmount() > 0; });
}

void UWorker::setEnabled(bool status)
{
	m_enabled = status;
}

void UWorker::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (m_status == Status::GettingWoodFromBarn && OtherActor == m_barnToGetWoodFrom)
	{
		m_owner->stopMovement();

		ABuilding* newBuilding = getBuildingToCarryWood();

		if (newBuilding != nullptr)
		{
			m_amountWoodCarrying = m_barnToGetWoodFrom->takeWood(c_maxAmountWoodCarrying - m_amountWoodCarrying);
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
		m_barnToGetWoodFrom = nullptr;
		m_buildingToCarryWoodTo = nullptr;
		m_status = Status::WaitingForBuilding;
	}
}