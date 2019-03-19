#pragma once

#include "Classes/Materials/Material.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class EXILE_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	enum class Status
	{
		InGame,
		Placing,
		Unknown
	};

	ABuilding();
	virtual void Tick(float DeltaTime) override;

	void setStatus(Status status);
	Status getStatus();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UMaterial* unableToBuildMaterial;

protected:
	virtual void BeginPlay() override;

private:
	Status m_status = Status::Unknown;
};
