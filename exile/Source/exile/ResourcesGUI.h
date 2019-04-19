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
	void setNumResidents(uint16 numResidents);
	void setNumTreeCutters(uint16 numTreeCutters);
	void setNumBuilders(uint16 numBuilders);
	void setNumWorkers(uint16 numWorkers);
	void setNumGatherers(uint16 numGatherers);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_amountWood = "0";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_numResidents = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_numTreeCutters = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_numBuilders = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_numWorkers = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_numGatherers = "0";

private:
	UPROPERTY(VisibleAnywhere)
		AMyGameMode* m_gameMode = nullptr;
};
