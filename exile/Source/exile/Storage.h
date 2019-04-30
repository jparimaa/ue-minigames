#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "MyGameMode.h"
#include "Storage.generated.h"

UCLASS()
class EXILE_API AStorage : public ABuilding
{
	GENERATED_BODY()

public:
	enum class Resource
	{
		Wood, Food
	};

	AStorage();

	void addResource(Resource resource, uint16 amount);
	uint16 getResourceAmount(Resource resource);
	uint16 takeResource(Resource resource, uint16 maxAmount);
	uint16 getFreeSpace();

	virtual void onBuildingReady();

	UPROPERTY(EditAnywhere)
		UMaterial* m_inGameMaterial;

	UPROPERTY(EditAnywhere)
		bool m_readyAtStart = false;

	UPROPERTY(EditAnywhere)
		uint16 m_initialFoodAmount = 0;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		uint16 m_maxCapacity = 10000;

	UPROPERTY(VisibleAnywhere)
		uint16 m_woodAmount = 0;

	UPROPERTY(VisibleAnywhere)
		uint16 m_foodAmount = 0;

	AMyGameMode* m_gameMode = nullptr;
};
