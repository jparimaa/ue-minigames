#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Resident.generated.h"

UCLASS()
class EXILE_API AResident : public APawn
{
	GENERATED_BODY()

public:
	AResident();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void FindNearestActor();

	AActor* NearestActor = nullptr;
	FVector Direction;
	float Speed = 100.0f;
};
