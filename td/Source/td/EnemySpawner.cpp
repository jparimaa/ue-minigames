#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

namespace
{
	TMap<FString, AEnemySpawner::EEnemyType> StringToEnemyType
	{
		{FString("light"), AEnemySpawner::EEnemyType::Light},
		{FString("heavy"), AEnemySpawner::EEnemyType::Heavy}
	};
}

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

	const TArray<TSharedPtr<FJsonValue>> WavesData = JsonObject->GetArrayField("waves");

	for (int32 i = 0; i < WavesData.Num(); ++i)
	{
		TArray<FPack>& Packs = EnemyWaves.AddZeroed_GetRef();
		const TArray<TSharedPtr<FJsonValue>> PacksData = WavesData[i]->AsObject()->GetArrayField("packs");
		for (int32 j = 0; j < PacksData.Num(); ++j)
		{
			TSharedPtr<FJsonObject> PackData = PacksData[j]->AsObject();
			if (!StringToEnemyType.Contains(PackData->GetStringField("type"))) {
				continue;
			}
			FPack& Pack = Packs.AddZeroed_GetRef();
			Pack.Count = PackData->GetIntegerField("count");
			Pack.Type = StringToEnemyType[PackData->GetStringField("type")];
		}
	}
}