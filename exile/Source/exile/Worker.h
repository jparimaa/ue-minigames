#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Worker.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UWorker : public UActorComponent
{
	GENERATED_BODY()
public:
	UWorker();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setEnabled(bool status);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;
};
