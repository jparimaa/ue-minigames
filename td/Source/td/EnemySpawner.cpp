#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	LastSpawnTime = std::chrono::system_clock::now();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto Now = std::chrono::system_clock::now();
	if (Now - LastSpawnTime > std::chrono::seconds(3)) {
		LastSpawnTime = Now;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		check(FoundActors.Num() != 0);
		const AActor* ChosenActor = FoundActors[0];

		const FTransform Transform(ChosenActor->GetActorLocation());
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor(EnemyClass.Get(), &Transform, SpawnParameters);
	}
}

