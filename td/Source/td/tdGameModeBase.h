#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "tdGameModeBase.generated.h"

class UMainGUI;

UCLASS()
class TD_API AtdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AtdGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> MainGUIClass;

private:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UMainGUI* MainGUI = nullptr;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;
};
