#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> WaypointActors;

	UPROPERTY(VisibleAnywhere)
		AActor* CurrentWaypoint = nullptr;

	int CurrentWaypointNumber = 0;

	bool Moving = false;
};
