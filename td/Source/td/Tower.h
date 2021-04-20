#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TD_API ATower : public AActor
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
