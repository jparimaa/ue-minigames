#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCamera.generated.h"

UCLASS()
class TD_API AMainCamera : public APawn
{
	GENERATED_BODY()

public:
	AMainCamera();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void RotateRight(float Value);

	FVector MovementInput;
	float YawValue = 0.0f;
};
