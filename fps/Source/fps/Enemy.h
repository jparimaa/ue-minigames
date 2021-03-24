// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AAIController;

UCLASS()
class FPS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Kill();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		AAIController* AIController = nullptr;

	UPROPERTY(VisibleAnywhere)
		AActor* MainPlayer = nullptr;

	UPROPERTY(VisibleAnywhere)
		bool Killed = false;

	std::chrono::time_point<std::chrono::system_clock> KillTime;
};
