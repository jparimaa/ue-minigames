#include "Builder.h"
#include "Resident.h"

namespace
{
const float c_buildTime = 5.0f;
}

UBuilder::UBuilder()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuilder::BeginPlay()
{
	Super::BeginPlay();

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UBuilder::OnOverlapBegin);
}

void UBuilder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}

	if (m_status == Status::WaitingForBuilding && m_buildingToConstruct == nullptr)
	{
		m_buildingToConstruct = getBuildingToConstruct();
		if (m_buildingToConstruct != nullptr)
		{
			m_status = Status::WalkingToBuilding;
			m_owner->moveToActor(m_buildingToConstruct);
		}
	}

	if (m_status == Status::WalkingToBuilding)
	{
		check(m_buildingToConstruct != nullptr);
		ABuilding* newBuilding = getBuildingToConstruct();
		if (newBuilding == nullptr)
		{
			m_status = Status::WaitingForBuilding;
			m_owner->stopMovement();
		}
		else if (newBuilding != m_buildingToConstruct)
		{
			m_owner->moveToActor(newBuilding);
		}
		m_buildingToConstruct = newBuilding;
	}

	if (m_status == Status::WalkingToBuilding && m_owner->getMoveStatus() == EPathFollowingStatus::Idle)
	{
		check(m_buildingToConstruct != nullptr);
		if (FVector::Distance(m_owner->GetActorLocation(), m_buildingToConstruct->GetActorLocation()) < 300.0f)
		{
			m_status = Status::Building;
		}
	}

	if (m_status == Status::Building)
	{
		if (m_buildingToConstruct->getConstructionPointsRequired() == 0)
		{
			m_status = Status::WaitingForBuilding;
		}
		else
		{
			m_currentBuildTime += DeltaTime;
			if (m_currentBuildTime > c_buildTime)
			{
				m_currentBuildTime = 0.0f;
				m_buildingToConstruct->addConstructionPoints(1);
			}
		}
	}
}

void UBuilder::setEnabled(bool status)
{
	m_enabled = status;
	if (!m_enabled)
	{
		m_status = Status::WaitingForBuilding;
		m_buildingToConstruct = nullptr;
	}
}

void UBuilder::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (m_status == Status::WalkingToBuilding && OtherActor == m_buildingToConstruct)
	{
		m_owner->stopMovement();
		m_status = Status::Building;
	}
}

ABuilding* UBuilder::getBuildingToConstruct()
{
	return m_owner->findNearestActor<ABuilding>([](ABuilding* building) {
		return building->getStatus() == ABuilding::Status::Constructing;
	});
}