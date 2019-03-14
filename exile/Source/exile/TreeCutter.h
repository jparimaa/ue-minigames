#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Tree.h"
#include "Barn.h"
#include "TreeCutter.generated.h"

class AResident;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UTreeCutter : public UActorComponent
{
	GENERATED_BODY()

public:
	UTreeCutter();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void setEnabled(bool status);

protected:
	virtual void BeginPlay() override;

private:
	enum class Status
	{
		WalkingToCut,
		Cutting,
		ReturningWoodToBarn
	};

	void startCutting();
	void returnWood();

	AResident* m_owner = nullptr;

	Status m_status = Status::WalkingToCut;

	UPROPERTY(VisibleAnywhere)
		ABarn* m_barnToReturn = nullptr;

	UPROPERTY(VisibleAnywhere)
		ATree* m_treeToBeCutted = nullptr;

	UPROPERTY(VisibleAnywhere)
		uint16 m_amountOfWoodOwned = 0;

	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;
};
