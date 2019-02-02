#include "Resident.h"
#include "Tree.h"
#include "Classes/Components/SphereComponent.h"

#include <limits>

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();
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
	FVector NewLocation = GetActorLocation();
	NewLocation += Direction * DeltaTime * Speed;
	SetActorLocation(NewLocation);
}

void AResident::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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