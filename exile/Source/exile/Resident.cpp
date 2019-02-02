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

	USphereComponent* sphereComponent = Cast< USphereComponent>(GetDefaultSubobjectByName(TEXT("Sphere")));
	if (sphereComponent)
	{
		sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AResident::OnOverlapBegin);
	}

	FindNearestActor();
	if (NearestActor != nullptr)
	{
		Direction = NearestActor->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
}

void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_reachedDestination)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += Direction * DeltaTime * Speed;
		SetActorLocation(NewLocation);
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
	}
}

void AResident::FindNearestActor()
{
	TArray<AActor*> OverlappingActors; 
	TSubclassOf<ATree> Filter;
	GetOverlappingActors(OverlappingActors, Filter);
	float SmallestDistance = std::numeric_limits<float>::max();
	
	for (AActor* Actor : OverlappingActors)
	{
		float Distance = Actor->GetDistanceTo(this);
		SmallestDistance = Distance > SmallestDistance ? Distance : SmallestDistance;
		NearestActor = Actor;
	}
}