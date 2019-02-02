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

	UPROPERTY(EditAnywhere)
		uint16 Health = 100;

	UPROPERTY(EditAnywhere)
		uint16 Yield = 100;

protected:
	virtual void BeginPlay() override;	
};
