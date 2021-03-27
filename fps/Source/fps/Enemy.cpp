#include "Enemy.h"
#include "MainPlayer.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "MyGameMode.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(100.0f);
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
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
	if (MainPlayer && AIController && !IsMovementStopped)
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
	if (Killed) {
		return;
	}

	StopMovement();

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
	AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GetGameData()->EnemyKillCount += 1;
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->GetName() == FString("MainPlayer_BP_C") && !Killed) {
		AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->GameOver();
	}
}

void AEnemy::StopMovement(int msgIndex)
{
	IsMovementStopped = true;
	AIController->StopMovement();
}