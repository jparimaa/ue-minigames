#include "tdGameModeBase.h"

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
}

void AtdGameModeBase::AddEnemyPassed()
{
	++EnemiesPassed;
	if (MainGUI)
	{
		MainGUI->EnemiesPassed = FString::FromInt(EnemiesPassed);
	}
	if (EnemiesPassed > 0) {
		MainGUI->OnGameOver();
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