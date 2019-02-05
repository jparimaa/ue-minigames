#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Resident.h"
#include "Tree.h"
#include "TreeCutter.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UTreeCutter : public UActorComponent
{
	GENERATED_BODY()

public:
	UTreeCutter();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	enum class Status
	{
		WalkingToCut,
		Cutting,
		TransportingWoodToBarn
	};

	void startCutting(AActor* tree);

	AResident* m_owner = nullptr;
	USphereComponent* m_sphereTrigger = nullptr;

	Status m_status = Status::WalkingToCut;

	UPROPERTY(VisibleAnywhere)
		AActor* m_nearestTree = nullptr;

	UPROPERTY(VisibleAnywhere)
		AActor* m_nearestBarn = nullptr;

	UPROPERTY(VisibleAnywhere)
		ATree* m_treeToBeCutted = nullptr;

	UPROPERTY(VisibleAnywhere)
		FVector m_direction;

	UPROPERTY(VisibleAnywhere)
		uint16 m_amountOfWoodOwned = 0;
};
