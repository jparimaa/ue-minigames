#pragma once

#include "Storage.h"
#include "Building.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Worker.generated.h"

class AResident;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UWorker : public UActorComponent
{
	GENERATED_BODY()
public:
	UWorker();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setEnabled(bool status);

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	enum class Status
	{
		GettingWoodFromStorage,
		CarryingWoodToBuilding,
		WaitingForWood,
		WaitingForBuilding
	};

	ABuilding* getBuildingToCarryWood();
	AStorage* getStorageWithWood();

	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;

	AResident* m_owner = nullptr;

	Status m_status = Status::WaitingForBuilding;

	UPROPERTY(VisibleAnywhere)
		AStorage* m_storageToGetWoodFrom = nullptr;
	UPROPERTY(VisibleAnywhere)
		ABuilding* m_buildingToCarryWoodTo = nullptr;

	UPROPERTY(VisibleAnywhere)
		uint16 m_amountWoodCarrying = 0;
};
