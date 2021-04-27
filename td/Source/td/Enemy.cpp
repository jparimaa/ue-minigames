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

void AEnemy::Damage(int Amount)
{
	Health -= Amount;
	if (Health < 0) {
		Alive = false;
		Destroy();
	}
}

bool AEnemy::IsAlive()
{
	return Alive;
}
