#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class EXILE_API ATree : public AActor
{
	GENERATED_BODY()

public:
	ATree();
	virtual void Tick(float DeltaTime) override;
	bool cut(uint16 damage, uint16& yield);

	uint16_t getYield();
	bool isFullGrown();

	UPROPERTY(EditAnywhere)
		uint16 m_health = 100;

protected:
	virtual void BeginPlay() override;

private:
	float m_yield = 0;
	bool m_isFullGrown = false;
};
