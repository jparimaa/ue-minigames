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

	UPROPERTY(EditAnywhere)
		int MaxHealth;

	int CurrentHealth;

	UPROPERTY(BlueprintReadOnly)
		float HealthPercentage = 1.0f;

private:
	bool Alive = true;
};
