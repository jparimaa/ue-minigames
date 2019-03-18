#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class EXILE_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	ABuilding();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
