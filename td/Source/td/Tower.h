#pragma once

#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TD_API ATower : public AActor
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	const TArray<AEnemy*>& GetEnemiesInRange() const;
	void RemoveEnemyFromRange(AEnemy* Enemy);

	void SetIsFiring(bool Status);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		bool IsFiring = false;

private:
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereComp = nullptr;

	UPROPERTY(VisibleAnywhere)
		TArray<AEnemy*> EnemiesInRange;
};
