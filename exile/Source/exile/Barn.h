#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameMode.h"

#include "Barn.generated.h"

UCLASS()
class EXILE_API ABarn : public AActor
{
	GENERATED_BODY()

public:
	ABarn();
	void addWood(uint16 amount);
	uint16 getWoodAmount();
	uint16 getFreeSpace();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		uint16 m_maxCapacity = 10000;

	UPROPERTY(VisibleAnywhere)
		uint16 m_woodAmount = 0;

	AMyGameMode* m_gameMode = nullptr;
};
