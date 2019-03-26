#pragma once

#include "Building.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

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

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AHouse> m_houseClass;

protected:
	virtual void BeginPlay() override;

private:
	void setupInputComponent(UInputComponent* myInputComponent);

	UFUNCTION()
		void spawnBuilding();

	UCameraComponent* m_mainCamera = nullptr;
	APlayerController* m_playerController = nullptr;
	ABuilding* m_currentBuilding = nullptr;
	bool m_placing = true;
};
