#include "TreeCutter.h"
#include "Tree.h"

UTreeCutter::UTreeCutter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTreeCutter::BeginPlay()
{
	Super::BeginPlay();

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	if (sphereComponent)
	{
		sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UTreeCutter::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("##### TreeCutter sphereComponent is null"));
	}
}

void UTreeCutter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_status == Status::WalkingToCut)
	{
		if (m_nearestTree == nullptr)
		{
			m_nearestTree = m_owner->findNearestActor<ATree>();
			m_direction = m_owner->getDirectionTo(m_nearestTree);
		}

		m_owner->move(m_direction * DeltaTime);
	}
	else if (m_status == Status::Cutting)
	{
		uint16 yield = 0;
		if (m_treeToBeCutted->cut(1, yield))
		{
			m_amountOfWoodOwned = yield;
			m_status = Status::TransportingWoodToBarn;
			m_treeToBeCutted = nullptr;
		}
	}
	else if (m_status == Status::TransportingWoodToBarn)
	{
		if (m_nearestBarn == nullptr)
		{
			m_nearestBarn = m_owner->findNearestBarnWithSpace(m_amountOfWoodOwned);
			m_direction = m_owner->getDirectionTo(m_nearestBarn);
		}

		m_owner->move(m_direction * DeltaTime);
	}
}

void UTreeCutter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ATree::StaticClass()))
	{
		if (m_status == Status::WalkingToCut)
		{
			startCutting(OtherActor);
		}
	}
}

void UTreeCutter::startCutting(AActor* tree)
{
	m_status = Status::Cutting;
	m_treeToBeCutted = Cast<ATree>(tree);
	m_direction.Set(0.0f, 0.0f, 0.0f);
	m_nearestTree = nullptr;
}