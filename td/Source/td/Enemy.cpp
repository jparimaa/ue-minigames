#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Waypoint")), WaypointActors);
	for (int i = 0; i < WaypointActors.Num(); i++) {
		AActor* Waypoint = WaypointActors[i];
		if (Waypoint->GetName() == FString("WP0"))
		{
			CurrentWaypoint = WaypointActors[i];
			break;
		}
	}

	AIController = Cast<AAIController>(GetController());

	if (AIController && CurrentWaypoint)
	{
		AIController->MoveToActor(CurrentWaypoint);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
