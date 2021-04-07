#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "tdGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TowerTile.generated.h"

UCLASS()
class TD_API ATowerTile : public AActor
{
	GENERATED_BODY()

public:
	ATowerTile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnClick(AActor* Actor, FKey ButtonPressed);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComp;

	AtdGameModeBase* GameMode;
};
