#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MainCamera.generated.h"

UCLASS()
class EXILE_API AMainCamera : public APawn
{
	GENERATED_BODY()

public:
	AMainCamera();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void moveForward(float Value);

	UFUNCTION()
		void moveRight(float Value);

	UFUNCTION()
		void moveUp();

	UFUNCTION()
		void moveDown();

	UPROPERTY(EditAnywhere)
		float m_mouseSensitivity = 3.0f;

protected:
	virtual void BeginPlay() override;

	FVector m_movementInput;
};
