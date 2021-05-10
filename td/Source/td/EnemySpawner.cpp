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
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	LastSpawnTime = std::chrono::system_clock::now();
	LoadEnemySpawnData();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	check(FoundActors.Num() != 0);
	SpawnPoint = FTransform(FoundActors[0]->GetActorLocation());
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Running)
	{
		return;
	}

	using namespace std::chrono;

	const auto Now = std::chrono::system_clock::now();
	if (Now - WaveEndTime < seconds(5)) {
		return;
	}

	if (Now - LastSpawnTime < milliseconds(500)) {
		return;
	}

	LastSpawnTime = Now;

	const int PreviousWaveIndex = WaveIndex;

	Running = UpdateSpawnIndices();
	if (!Running) {
		return;
	}

	if (PreviousWaveIndex != WaveIndex) {
		WaveEndTime = std::chrono::system_clock::now();
		return;
	}

	const FPack Pack = EnemyWaves[WaveIndex][PackIndex];
	const EEnemyType EnemyType = Pack.Type;
	if (EnemyType == EEnemyType::Light)
	{
		GetWorld()->SpawnActor(LightEnemyClass.Get(), &SpawnPoint, SpawnParameters);
	}
	else if (EnemyType == EEnemyType::Heavy)
	{
		GetWorld()->SpawnActor(HeavyEnemyClass.Get(), &SpawnPoint, SpawnParameters);
	}
	else
	{
		Running = false;
		UE_LOG(LogTemp, Error, TEXT("Incorrect enemy type, disabling enemy spawning"));
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

bool AEnemySpawner::UpdateSpawnIndices()
{
	++EnemyIndex;
	if (EnemyIndex > EnemyWaves[WaveIndex][PackIndex].Count)
	{
		EnemyIndex = 1;
		++PackIndex;
	}
	if (PackIndex == EnemyWaves[WaveIndex].Num())
	{
		PackIndex = 0;
		EnemyIndex = 0;
		++WaveIndex;
	}
	if (WaveIndex == EnemyWaves.Num())
	{
		return false;
	}
	return true;
}