#include "TreeCutter.h"

#include <limits>

UTreeCutter::UTreeCutter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTreeCutter::BeginPlay()
{
	Super::BeginPlay();

	USphereComponent* sphereComponent = Cast<USphereComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Sphere")));
	if (sphereComponent)
	{
		sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UTreeCutter::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("##### TreeCutter sphereComponent is null"));
	}

	findNearestActor();
	if (m_nearestActor != nullptr)
	{
		m_direction = m_nearestActor->GetActorLocation() - GetOwner()->GetActorLocation();
		m_direction.Normalize();
	}
}

void UTreeCutter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_reachedDestination)
	{
		FVector NewLocation = GetOwner()->GetActorLocation();
		NewLocation += m_direction * DeltaTime * m_speed;
		GetOwner()->SetActorLocation(NewLocation);
	}

	if (m_cutting)
	{
		uint16 yield = 0;
		if (m_treeToBeCutted->cut(1, yield))
		{
			m_cutting = false;
			m_reachedDestination = false;
			m_direction *= -1.0f;
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
	if (OtherActor->GetClass()->IsChildOf(ATree::StaticClass()))
	{
		m_reachedDestination = true;
		startCutting(OtherActor);
	}
}

void UTreeCutter::findNearestActor()
{
	TArray<AActor*> OverlappingActors;
	TSubclassOf<ATree> Filter;
	GetOwner()->GetOverlappingActors(OverlappingActors, Filter);
	float SmallestDistance = std::numeric_limits<float>::max();

	for (AActor* Actor : OverlappingActors)
	{
		float Distance = Actor->GetDistanceTo(GetOwner());
		SmallestDistance = Distance > SmallestDistance ? Distance : SmallestDistance;
		m_nearestActor = Actor;
	}
}

void UTreeCutter::startCutting(AActor* actor)
{
	m_treeToBeCutted = Cast<ATree>(actor);
	m_cutting = true;
}