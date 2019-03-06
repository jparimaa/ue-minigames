#pragma once

#include "Tree.h"

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "TreeSpawner.generated.h"
UCLASS()
class EXILE_API ATreeSpawner : public AInfo
{
	GENERATED_BODY()

public:
	ATreeSpawner();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATree> m_classToSpawn;

protected:
	virtual void BeginPlay() override;

private:
	float m_counter = 0.0f;
};
