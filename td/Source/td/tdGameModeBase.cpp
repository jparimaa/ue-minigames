#include "tdGameModeBase.h"
#include "MainGUI.h"

AtdGameModeBase::AtdGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AtdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(MainGUIClass);
}

void AtdGameModeBase::Tick(float DeltaTime)
{
	if (MainGUI)
	{
		int32 EnemiesPassedInt = FCString::Atoi(*MainGUI->EnemiesPassed);
		++EnemiesPassedInt;
		MainGUI->EnemiesPassed = FString::FromInt(EnemiesPassedInt);
	}
}

void AtdGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
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
			MainGUI = Cast<UMainGUI>(CurrentWidget);
		}
	}
}