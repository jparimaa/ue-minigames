#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

UCLASS()
class EXILE_API AHouse : public AActor
{
	GENERATED_BODY()

public:
	AHouse();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
