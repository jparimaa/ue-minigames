#include "Enemy.h"
#include "EnemyAIController.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::Damage(float Amount)
{
	Health -= Amount;
	if (Health < 0.0f) {
		Health = 0.0f;
		Alive = false;
		Destroy();
	}
}

bool AEnemy::IsAlive()
{
	return Alive;
}
