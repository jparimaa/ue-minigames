#include "Worker.h"
#include "Resident.h"

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
		m_buildingToCarryWoodTo = m_owner->findNearestActor<ABuilding>(
			[](ABuilding* building) { return building->getStatus() == ABuilding::Status::Constructing; });
		if (m_buildingToCarryWoodTo != nullptr)
		{
			m_status = Status::WaitingForWood;
		}
	}

	if (m_status == Status::WaitingForWood && m_barnToGetWoodFrom == nullptr)
	{
		check(m_buildingToCarryWoodTo != nullptr);
		m_barnToGetWoodFrom = m_owner->findNearestActor<ABarn>([](ABarn* barn) { return barn->getWoodAmount() > 0; });
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
		ABarn* newBarn = m_owner->findNearestActor<ABarn>([](ABarn* barn) { return barn->getWoodAmount() > 0; });
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

}