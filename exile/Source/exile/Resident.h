#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Classes/Components/SphereComponent.h"

#include "Tree.h"

#include "Resident.generated.h"

UCLASS()
class EXILE_API AResident : public APawn
{
	GENERATED_BODY()

public:
	AResident();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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
