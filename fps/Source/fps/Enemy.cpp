#include "Enemy.h"
#include "MainPlayer.h"
#include "AIController.h"
#include "EngineUtils.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());
	for (TActorIterator<AMainPlayer> iter(GetWorld()); iter; ++iter)
	{
		MainPlayer = *iter;
		break;
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MainPlayer && AIController)
	{
		AIController->MoveToActor(MainPlayer);
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

