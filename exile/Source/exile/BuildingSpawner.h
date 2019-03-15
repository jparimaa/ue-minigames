#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingSpawner.generated.h"

UCLASS()
class EXILE_API ABuildingSpawner : public AActor
{
	GENERATED_BODY()

public:
	ABuildingSpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
