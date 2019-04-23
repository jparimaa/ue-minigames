#include "Gatherer.h"
#include "Resident.h"
#include "Classes/Components/SphereComponent.h"

UGatherer::UGatherer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGatherer::BeginPlay()
{
	Super::BeginPlay();

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UGatherer::OnOverlapBegin);
}

void UGatherer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}

	//UE_LOG(LogTemp, Log, TEXT("##### UGatherer::TickComponent"));

	if (m_status == Status::WalkingToGatherable && m_resourceToGather == nullptr)
	{
		m_resourceToGather = m_owner->findNearestActor<AGatherable>([](AGatherable* gatherable) { return !gatherable->isTargetLocked(); });
		if (m_resourceToGather != nullptr)
		{
			m_resourceToGather->setTargetLock(true);
			m_owner->moveToActor(m_resourceToGather);
		}
	}

	if (m_status == Status::ReturningGatherable)
	{
		m_storageToReturn = m_owner->findNearestStorageWithSpace(m_amountOfFoodOwned);
		if (m_storageToReturn != nullptr)
		{
			m_owner->moveToActor(m_storageToReturn);
		}
	}
}

void UGatherer::setEnabled(bool status)
{
	m_enabled = status;
	if (status == false)
	{
		if (m_owner != nullptr)
		{
			m_owner->stopMovement();
		}
		m_status = Status::WalkingToGatherable;
		m_storageToReturn = nullptr;
		if (m_resourceToGather != nullptr)
		{
			m_resourceToGather->setTargetLock(false);
		}
		m_resourceToGather = nullptr;
		m_amountOfFoodOwned = 0;
	}
}

void UGatherer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (m_status == Status::WalkingToGatherable && OtherActor == m_resourceToGather)
	{
		m_owner->stopMovement();
		m_amountOfFoodOwned = m_resourceToGather->gather();
		m_status = Status::ReturningGatherable;
	}
	else if (m_status == Status::ReturningGatherable && OtherActor == m_storageToReturn)
	{
		m_owner->stopMovement();
		m_storageToReturn->addResource(AStorage::Resource::Food, m_amountOfFoodOwned);
		m_amountOfFoodOwned = 0;
		m_storageToReturn = nullptr;
		m_resourceToGather = nullptr;
		m_status = Status::WalkingToGatherable;
	}
}