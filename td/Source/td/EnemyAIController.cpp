#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Navigation/PathFollowingComponent.h"
#include "tdGameModeBase.h"

AEnemyAIController::AEnemyAIController()
{
	bStartAILogicOnPossess = true;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Waypoint")), WaypointActors);
	for (int i = 0; i < WaypointActors.Num(); i++) {
		AActor* Waypoint = WaypointActors[i];
		if (Waypoint->GetName().Compare(FString("WP0")) == 0)
		{
			CurrentWaypoint = Waypoint;
			break;
		}
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Moving) {
		ControlledPawn = GetPawn();

		check(CurrentWaypoint);
		const EPathFollowingRequestResult::Type Result = MoveToActor(CurrentWaypoint);
		if (Result == EPathFollowingRequestResult::RequestSuccessful)
		{
			Moving = true;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Unable to move to waypoint %s "), *CurrentWaypoint->GetName());
		}
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	++CurrentWaypointNumber;

	if (CurrentWaypointNumber > WaypointActors.Num())
	{
		AtdGameModeBase* GameMode = Cast<AtdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->AddEnemyPassed();
		ControlledPawn->Destroy();
		Destroy();
		return;
	}
	else if (CurrentWaypointNumber == WaypointActors.Num()) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		check(FoundActors.Num() == 1);
		CurrentWaypoint = FoundActors[0];
	}
	else {
		for (int i = 0; i < WaypointActors.Num(); i++) {
			if (i == CurrentWaypointNumber) {
				CurrentWaypoint = WaypointActors[i];
				break;
			}
		}
	}

	MoveToActor(CurrentWaypoint);
}