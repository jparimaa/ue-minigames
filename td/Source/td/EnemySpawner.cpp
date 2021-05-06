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
	LoadEnemySpawnData();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SpawnCount >= MaxSpawnCount)
	{
		return;
	}

	const auto Now = std::chrono::system_clock::now();
	if (Now - LastSpawnTime > std::chrono::milliseconds(SpawnIntervalMS)) {
		LastSpawnTime = Now;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		check(FoundActors.Num() != 0);
		const AActor* ChosenActor = FoundActors[0];

		const FTransform Transform(ChosenActor->GetActorLocation());
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor(EnemyClass.Get(), &Transform, SpawnParameters);
		++SpawnCount;
	}
}

void AEnemySpawner::LoadEnemySpawnData()
{
	const FString JsonFilePath = FPaths::ProjectContentDir() + "EnemySpawnData/level1.json";
	FString JsonString;

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (!(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to deserialize json %s"), *JsonFilePath);
		return;
	}

	const TArray<TSharedPtr<FJsonValue>> Waves = JsonObject->GetArrayField("waves");

	for (int32 i = 0; i < Waves.Num(); ++i)
	{
		const TArray<TSharedPtr<FJsonValue>> Packs = Waves[i]->AsObject()->GetArrayField("packs");
		for (int32 j = 0; j < Packs.Num(); ++j)
		{
			TSharedPtr<FJsonObject> Pack = Packs[j]->AsObject();
			UE_LOG(LogTemp, Log, TEXT("Type %s, count %d"), *Pack->GetStringField("type"), Pack->GetIntegerField("count"));
		}
	}
}