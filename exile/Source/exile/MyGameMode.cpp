#include "MyGameMode.h"
#include "ResourcesGUI.h"
#include "Barn.h"
#include "EngineUtils.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AMyGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	UE_LOG(LogTemp, Log, TEXT("AMyGameMode::ChangeMenuWidget"));
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AMyGameMode::updateResources()
{
	uint16 totalWoodAmount = 0;
	for (TActorIterator<ABarn> iter(GetWorld()); iter; ++iter)
	{
		totalWoodAmount += iter->getWoodAmount();
	}
	m_resourcesGUI->setAmountWood(totalWoodAmount);
}

void AMyGameMode::setResourcesGUI(UResourcesGUI* resourcesGUI)
{
	m_resourcesGUI = resourcesGUI;
}