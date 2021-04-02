#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGUI.generated.h"

class AtdGameModeBase;

UCLASS()
class TD_API UMainGUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString EnemiesPassed = "0";

private:
	UPROPERTY(VisibleAnywhere)
		AtdGameModeBase* GameMode = nullptr;
};
