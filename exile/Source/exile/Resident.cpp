#include "Resident.h"
#include "Tree.h"

#include <limits>

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();

	USphereComponent* sphereComponent = Cast<USphereComponent>(GetDefaultSubobjectByName(TEXT("Sphere")));
	if (sphereComponent)
	{
		sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AResident::OnOverlapBegin);
	}

	findNearestActor();
	if (m_nearestActor != nullptr)
	{
		m_direction = m_nearestActor->GetActorLocation() - GetActorLocation();
		m_direction.Normalize();
	}
}

void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_reachedDestination)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += m_direction * DeltaTime * m_speed;
		SetActorLocation(NewLocation);
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

void AResident::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AResident::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
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

void AResident::findNearestActor()
{
	TArray<AActor*> OverlappingActors; 
	TSubclassOf<ATree> Filter;
	GetOverlappingActors(OverlappingActors, Filter);
	float SmallestDistance = std::numeric_limits<float>::max();
	
	for (AActor* Actor : OverlappingActors)
	{
		float Distance = Actor->GetDistanceTo(this);
		SmallestDistance = Distance > SmallestDistance ? Distance : SmallestDistance;
		m_nearestActor = Actor;
	}
}

void AResident::startCutting(AActor* actor)
{
	m_treeToBeCutted = Cast<ATree>(actor);
	m_cutting = true;
}