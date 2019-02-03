#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
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
	void findNearestActor();
	void startCutting(AActor* actor);

	AActor* m_nearestActor = nullptr;
	FVector m_direction;
	float m_speed = 100.0f;
	USphereComponent* m_sphereTrigger = nullptr;
	bool m_reachedDestination = false;

	bool m_cutting = false;
	ATree* m_treeToBeCutted = nullptr;
};
