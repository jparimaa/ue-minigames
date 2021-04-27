#pragma once

#include "EnemyAIController.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Enemy.generated.h"

UCLASS()
class TD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	void Damage(int Amount);
	bool IsAlive();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		int Health = 1000;

	bool Alive = true;
};
