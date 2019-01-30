// Fill out your copyright notice in the Description page of Project Settings.

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
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* RTSCameraComponent;

protected:
	virtual void BeginPlay() override;

	FVector MovementInput;

};
