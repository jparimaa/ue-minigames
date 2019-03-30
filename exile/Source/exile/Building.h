#pragma once

#include "InfoText.h"

#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class EXILE_API ABuilding : public AActor
{
	GENERATED_BODY()

public:

	enum class Type
	{
		House = 1
	};

	enum class Status
	{
		InGame,
		Placing,
		Constructing,
		Unknown
	};

	ABuilding();
	virtual void Tick(float DeltaTime) override;

	void setStatus(Status status);
	Status getStatus();

	void setProgressText(const FString& text);

	bool allowPlacing();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		UMaterial* m_unableToBuildMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* m_buildInProcessMaterial;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AInfoText> m_infoTextClass;

protected:
	virtual void BeginPlay() override;
	void setMaterial(UMaterialInterface* material);
	void setCollision(ECollisionEnabled::Type collision);

	AInfoText* m_infoText = nullptr;

private:
	Status m_status = Status::Unknown;
	TArray<UMaterialInterface*> m_originalMaterials;
	bool m_allowPlacing = true;
};
