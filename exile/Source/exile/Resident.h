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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
