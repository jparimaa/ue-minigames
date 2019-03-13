#pragma once

#include "CoreMinimal.h"
#include "Barn.h"
#include "GameFramework/Character.h"
#include "MyAIController.h"
#include "Worker.h"
#include "TreeCutter.h"
#include "Builder.h"

#include <limits>
#include <functional>

#include "Resident.generated.h"

UCLASS()
class EXILE_API AResident : public ACharacter
{
	GENERATED_BODY()

		enum class Profession
	{
		Worker,
		TreeCutter,
		Builder
	};

public:
	AResident();
	virtual void Tick(float DeltaTime) override;
	void setProfession(Profession profession);

	template<typename T>
	T* findNearestActor(std::function<bool(T*)> predicate = [](bool dummy) {return true; })
	{
		TArray<AActor*> overlappingActors;
		GetOverlappingActors(overlappingActors, T::StaticClass());
		float smallestDistance = std::numeric_limits<float>::max();
		AActor* nearestActor = nullptr;
		for (AActor* actor : overlappingActors)
		{
			if (!predicate(Cast<T>(actor)))
			{
				continue;
			}
			float distance = actor->GetDistanceTo(this);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				nearestActor = actor;
			}
		}
		return Cast<T>(nearestActor);
	}

	ABarn* findNearestBarnWithSpace(uint16 spaceRequired);
	void moveToActor(AActor* actor);
	void stopMovement();
	FVector getMoveDestination();

	UPROPERTY(VisibleAnywhere)
		FVector m_destination;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		float m_speed = 100.0f;

	UPROPERTY(VisibleAnywhere)
		AAIController* m_aiController;

	UWorker* m_worker = nullptr;
	UTreeCutter* m_treeCutter = nullptr;
	UBuilder* m_builder = nullptr;
};
