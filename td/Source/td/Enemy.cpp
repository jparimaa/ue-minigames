#include "Enemy.h"
#include "EnemyAIController.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MaxHealth = 100;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::Damage(int Amount)
{
	CurrentHealth -= Amount;
	HealthPercentage = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
	if (HealthPercentage < 0.0f) {
		HealthPercentage = 0.0f;
		Alive = false;
		Destroy();
	}
}

bool AEnemy::IsAlive()
{
	return Alive;
}
