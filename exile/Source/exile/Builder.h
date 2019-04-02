#pragma once

#include "Building.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Builder.generated.h"

class AResident;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UBuilder : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuilder();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setEnabled(bool status);

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	enum class Status
	{
		WaitingForBuilding,
		WalkingToBuilding,
		Building
	};

	ABuilding* getBuildingToConstruct();

	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;

	AResident* m_owner = nullptr;

	Status m_status = Status::WaitingForBuilding;

	UPROPERTY(VisibleAnywhere)
		ABuilding* m_buildingToConstruct = nullptr;

	float m_currentBuildTime = 0.0f;
};
