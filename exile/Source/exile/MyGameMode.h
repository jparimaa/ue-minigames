#pragma once

#include "Building.h"
#include "BuildingSpawner.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.generated.h"

class UResourcesGUI;

UCLASS()
class EXILE_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void changeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass);

	void setResourcesGUI(UResourcesGUI* resourcesGUI);

	void updateResources();

	void increaseNumResidents(int amount = 1);
	void decreaseNumResidents(int amount = 1);

	UFUNCTION(BlueprintCallable)
		void addNumTreeCutters(int amount = 1);

	UFUNCTION(BlueprintCallable)
		void addNumBuilders(int amount = 1);

	UFUNCTION(BlueprintCallable)
		void addNumGatherers(int amount = 1);

	UFUNCTION(BlueprintCallable)
		ABuildingSpawner* getBuildingSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> m_startingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> m_restartWidgetClass;

private:
	void addNumWorkers(int amount = 1);

	void updateToWorkers(int amount, int& profession);

	int decreaseResidentsFromProfession(int amount, int& profession);
	void checkNumResidentsAndProfessions();

	void updateResidentProfessions();

	UPROPERTY()
		UUserWidget* m_currentWidget;

	UResourcesGUI* m_resourcesGUI = nullptr;
	ABuildingSpawner* m_buildingSpawner = nullptr;

	int m_numResidents = 0;
	int m_numTreeCutters = 0;
	int m_numBuilders = 0;
	int m_numWorkers = 0;
	int m_numGatherers = 0;
};
