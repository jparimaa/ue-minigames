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
	AStorage();
	void addWood(uint16 amount);
	uint16 getWoodAmount();
	uint16 takeWood(uint16 maxAmount);
	uint16 getFreeSpace();

	virtual void setInGameMaterial();

	UPROPERTY(EditAnywhere)
		UMaterial* m_inGameMaterial;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		uint16 m_maxCapacity = 10000;

	UPROPERTY(VisibleAnywhere)
		uint16 m_woodAmount = 0;

	AMyGameMode* m_gameMode = nullptr;
};
