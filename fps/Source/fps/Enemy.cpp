#include "Enemy.h"
#include "MainPlayer.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	if (Killed && (std::chrono::system_clock::now() - KillTime) > std::chrono::seconds(3)) {
		Destroy();
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Kill()
{
	AIController->StopMovement();

	UCharacterMovementComponent* MovementComp = FindComponentByClass<UCharacterMovementComponent>();
	MovementComp->DisableMovement();
	TArray<UCapsuleComponent*> Comps;
	GetComponents(Comps);
	if (Comps.Num() > 0)
	{
		UCapsuleComponent* Comp = Comps[0];
		Comp->SetSimulatePhysics(true);
	}
	Killed = true;
	KillTime = std::chrono::system_clock::now();
}