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
	virtual void setInGameMaterial();

	UPROPERTY(EditAnywhere)
		UMaterial* m_inGameMaterial;

protected:
	virtual void BeginPlay() override;
};
