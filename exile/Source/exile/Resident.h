#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Barn.h"

#include <limits>

#include "Resident.generated.h"

UCLASS()
class EXILE_API AResident : public APawn
{
	GENERATED_BODY()

public:
	AResident();
	virtual void Tick(float DeltaTime) override;

	template<typename T>
	T* findNearestActor()
	{
		TArray<AActor*> overlappingActors;
		GetOverlappingActors(overlappingActors, T::StaticClass());
		float smallestDistance = std::numeric_limits<float>::max();
		AActor* nearestActor = nullptr;
		for (AActor* actor : overlappingActors)
		{
			float distance = actor->GetDistanceTo(this);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				nearestActor = actor;
			}
		}
		return Cast<T>(nearestActor);
	}

	AActor* findNearestBarnWithSpace(uint16 spaceRequired);
	FVector getDirectionTo(AActor* actor);
	void move(FVector direction);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		float m_speed = 100.0f;
};
