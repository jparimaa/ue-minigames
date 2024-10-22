// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class UInputComponent;
class UCameraComponent;
class USoundBase;

UCLASS()
class FPS_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DisableControls();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TSubclassOf<class ABullet> BulletClass;


protected:
	virtual void BeginPlay() override;

	void OnFire();

	UFUNCTION()
		void MoveForward(float Val);

	UFUNCTION()
		void MoveRight(float Val);

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* CameraComponent;
};
