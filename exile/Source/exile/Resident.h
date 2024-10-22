#pragma once

#include "CoreMinimal.h"
#include "Storage.h"
#include "MyAIController.h"
#include "Worker.h"
#include "TreeCutter.h"
#include "Builder.h"
#include "Gatherer.h"
#include "InfoText.h"

#include "GameFramework/Character.h"
#include "EngineUtils.h"

#include <limits>
#include <functional>

#include "Resident.generated.h"

UCLASS()
class EXILE_API AResident : public ACharacter
{
	GENERATED_BODY()

public:
	enum class Profession
	{
		Worker,
		TreeCutter,
		Builder,
		Gatherer
	};

	const TMap< Profession, FString> professionToString =
	{
		TPairInitializer<const Profession&, const FString&>(Profession::Worker, FString("Worker")),
		TPairInitializer<const Profession&, const FString&>(Profession::TreeCutter, FString("Tree cutter")),
		TPairInitializer<const Profession&, const FString&>(Profession::Builder, FString("Builder")),
		TPairInitializer<const Profession&, const FString&>(Profession::Gatherer, FString("Gatherer"))
	};

	AResident();
	virtual void Tick(float DeltaTime) override;
	void setProfession(Profession profession);
	Profession getProfession() const;

	template<typename T>
	T* findNearestActor(std::function<bool(T*)> predicate = [](bool dummy) {return true; })
	{
		float smallestDistance = std::numeric_limits<float>::max();
		AActor* nearestActor = nullptr;
		for (TActorIterator<T> iter(GetWorld()); iter; ++iter)
		{
			if (!predicate(Cast<T>(*iter)))
			{
				continue;
			}
			float distance = iter->GetDistanceTo(this);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				nearestActor = *iter;
			}
		}
		return Cast<T>(nearestActor);
	}

	AStorage* findNearestStorageWithSpace(uint16 spaceRequired);
	AStorage* findNearestStorageWithResource(AStorage::Resource resource, uint16 amount);
	void moveToActor(AActor* actor);
	void stopMovement();
	FVector getMoveDestination();
	EPathFollowingStatus::Type getMoveStatus();

	UPROPERTY(VisibleAnywhere)
		FVector m_destination;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AInfoText> m_infoTextClass;

protected:
	virtual void BeginPlay() override;

	AInfoText* m_infoText = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
		float m_speed = 100.0f;

	UPROPERTY(VisibleAnywhere)
		AAIController* m_aiController;

	Profession m_profession = Profession::Worker;
	UWorker* m_worker = nullptr;
	UTreeCutter* m_treeCutter = nullptr;
	UBuilder* m_builder = nullptr;
	UGatherer* m_gatherer = nullptr;

	float m_foodConsumptionTimer = 0.0f;
	uint16 m_timesWithoutFood = 0;
};
