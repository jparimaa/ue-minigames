#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.h"
#include "ResourcesGUI.generated.h"

UCLASS()
class EXILE_API UResourcesGUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void initGameMode();

	void setAmountWood(uint16 amountWood);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString m_amountWood = "0";

private:
	UPROPERTY(VisibleAnywhere)
		AMyGameMode* m_gameMode = nullptr;
};
