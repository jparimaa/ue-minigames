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
	void Damage(float Amount);
	bool IsAlive();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Health = 1.0f;

protected:
	virtual void BeginPlay() override;


private:
	bool Alive = true;
};
