#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gatherable.generated.h"

UCLASS()
class EXILE_API AGatherable : public AActor
{
	GENERATED_BODY()

public:
	AGatherable();
	virtual void Tick(float DeltaTime) override;

	uint16 gather();

	void setTargetLock(bool status);
	bool isTargetLocked();

protected:
	virtual void BeginPlay() override;

private:
	float m_yield = 0;
	bool m_targetLocked = false;
	bool m_isFullGrown = false;
};
