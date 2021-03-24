#include "MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	LastSpawnTime = std::chrono::system_clock::now();
}

void AMyGameMode::BeginPlay()
{
	if (!EnemyClass) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("EnemyClass not set!"));
		PrimaryActorTick.bStartWithTickEnabled = false;
		PrimaryActorTick.bCanEverTick = false;
	}
}

void AMyGameMode::Tick(float DeltaTime)
{
	const auto Now = std::chrono::system_clock::now();
	if ((Now - LastSpawnTime) > std::chrono::seconds(3))
	{
		LastSpawnTime = Now;
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		const AActor* ChosenActor = FoundActors[rand() % FoundActors.Num()];

		const FTransform Transform(ChosenActor->GetActorLocation());
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor(EnemyClass.Get(), &Transform, SpawnParameters);
	}
}