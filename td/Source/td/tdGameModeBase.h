// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "tdGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class TD_API AtdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AtdGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
