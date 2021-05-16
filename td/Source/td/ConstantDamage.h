#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstantDamage.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TD_API UConstantDamage : public UActorComponent
{
	GENERATED_BODY()

public:
	UConstantDamage();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		int Damage = 5;

	UPROPERTY(EditAnywhere)
		int FiringRateMS = 100;

	std::chrono::time_point<std::chrono::system_clock> LastFiringTime;
};
