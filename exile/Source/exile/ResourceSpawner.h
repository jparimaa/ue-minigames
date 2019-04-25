#pragma once

#include "Tree.h"
#include "Gatherable.h"

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ResourceSpawner.generated.h"

UCLASS()
class EXILE_API AResourceSpawner : public AInfo
{
	GENERATED_BODY()

public:
	struct SpawnSettings
	{
		float counter = 0.0f;
		float spawnTime = 0.0f;
		TSubclassOf<class AActor>* actorClass;
	};

	AResourceSpawner();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> m_treeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> m_gatherableClass;

protected:
	virtual void BeginPlay() override;

private:
	TArray<SpawnSettings> m_spawnSettings;
};
