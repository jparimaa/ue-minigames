#pragma once

#include "Storage.h"
#include "Gatherable.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gatherer.generated.h"

class AResident;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UGatherer : public UActorComponent
{
	GENERATED_BODY()

public:
	UGatherer();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setEnabled(bool status);

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	enum class Status
	{
		WalkingToGatherable,
		ReturningGatherable
	};

	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;

	AResident* m_owner = nullptr;

	Status m_status = Status::WalkingToGatherable;

	UPROPERTY(VisibleAnywhere)
		AGatherable* m_resourceToGather = nullptr;

	UPROPERTY(VisibleAnywhere)
		AStorage* m_storageToReturn = nullptr;

	UPROPERTY(VisibleAnywhere)
		uint16 m_amountOfFoodOwned = 0;
};
