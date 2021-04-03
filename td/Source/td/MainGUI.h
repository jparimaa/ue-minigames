#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGUI.generated.h"

UCLASS()
class TD_API UMainGUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString EnemiesPassed = "0";

	UFUNCTION(BlueprintImplementableEvent)
		void OnGameOver();
};
