#include "TreeCutter.h"
#include "Tree.h"
#include "Resident.h"

UTreeCutter::UTreeCutter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTreeCutter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("##### UTreeCutter::BeginPlay()"));

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UTreeCutter::OnOverlapBegin);
}

void UTreeCutter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_status == Status::WalkingToCut && m_treeToBeCutted == nullptr)
	{
		m_treeToBeCutted = m_owner->findNearestActor<ATree>([](ATree* tree) { return !tree->isTargetLocked(); });
		if (m_treeToBeCutted != nullptr)
		{
			m_treeToBeCutted->setTargetLock(true);
			m_owner->moveToActor(m_treeToBeCutted);
		}
	}
	else if (m_status == Status::Cutting)
	{
		uint16 yield = 0;
		if (m_treeToBeCutted->cut(1, yield))
		{
			m_amountOfWoodOwned = yield;
			m_status = Status::ReturningWoodToBarn;
			m_treeToBeCutted = nullptr;
		}
	}
	else if (m_status == Status::ReturningWoodToBarn && m_barnToReturn == nullptr)
	{
		m_barnToReturn = m_owner->findNearestBarnWithSpace(m_amountOfWoodOwned);
		if (m_barnToReturn != nullptr)
		{
			m_owner->moveToActor(m_barnToReturn);
		}
	}
}

void UTreeCutter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (m_status == Status::WalkingToCut && OtherActor == m_treeToBeCutted)
	{
		m_owner->stopMovement();
		startCutting();
	}
	else if (m_status == Status::ReturningWoodToBarn && OtherActor == m_barnToReturn)
	{
		m_owner->stopMovement();
		returnWood();
	}
}

void UTreeCutter::startCutting()
{
	m_status = Status::Cutting;
}

void UTreeCutter::returnWood()
{
	m_barnToReturn->addWood(m_amountOfWoodOwned);
	m_amountOfWoodOwned = 0;
	m_barnToReturn = nullptr;
	m_status = Status::WalkingToCut;
}