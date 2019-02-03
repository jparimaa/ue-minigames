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

protected:
	virtual void BeginPlay() override;
};
