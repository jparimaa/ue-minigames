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

	UFUNCTION(BlueprintCallable)
		void placeBuilding(int type);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AHouse> m_houseClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStorage> m_storageClass;

protected:
	virtual void BeginPlay() override;

private:
	void setupInputComponent(UInputComponent* myInputComponent);

	UFUNCTION()
		void spawnBuilding();

	UCameraComponent* m_mainCamera = nullptr;
	APlayerController* m_playerController = nullptr;
	ABuilding* m_currentBuilding = nullptr;
	bool m_placing = false;
};
