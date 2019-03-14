#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Builder.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXILE_API UBuilder : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuilder();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setEnabled(bool status);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		bool m_enabled = false;
};
