#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "House.generated.h"

UCLASS()
class EXILE_API AHouse : public ABuilding
{
	GENERATED_BODY()

public:
	AHouse();

protected:
	virtual void BeginPlay() override;
};
