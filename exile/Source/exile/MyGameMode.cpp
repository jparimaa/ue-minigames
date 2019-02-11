#include "MyGameMode.h"
#include "ResourcesGUI.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AMyGameMode::setResourcesGUI(UResourcesGUI* resourcesGUI)
{
	m_resourcesGUI = resourcesGUI;
	m_resourcesGUI->SetDisplayText(FText::FromString("Something"));
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