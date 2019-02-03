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

	UPROPERTY(EditAnywhere)
		uint16 m_health = 100;

	UPROPERTY(EditAnywhere)
		uint16 m_yield = 100;

protected:
	virtual void BeginPlay() override;
};
