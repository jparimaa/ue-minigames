#include "tdGameModeBase.h"
#include "MainPlayerController.h"
#include "MainCamera.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AtdGameModeBase::AtdGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void AtdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(MainGUIClass);

	for (TActorIterator<ATowerSpawner> iter(GetWorld()); iter; ++iter)
	{
		TowerSpawner = *iter;
		break;
	}
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

void AtdGameModeBase::ClickTile(AActor* Tile)
{
	LastClickedTile = Tile;
	MainGUI->OnTileClick();
}

void AtdGameModeBase::BuildTower(TowerType Type)
{
	if (TowerSpawner) {
		TowerSpawner->SpawnTower(Type, LastClickedTile);
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

