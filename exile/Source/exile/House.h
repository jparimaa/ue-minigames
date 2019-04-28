#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "Resident.h"
#include "House.generated.h"

UCLASS()
class EXILE_API AHouse : public ABuilding
{
	GENERATED_BODY()

public:
	AHouse();
	virtual void onBuildingReady();

	UPROPERTY(EditAnywhere)
		UMaterial* m_inGameMaterial;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AResident> m_residentClass;
};
