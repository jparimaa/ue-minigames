#include "GameHUD.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	const float Scale = 4.0f;
}

void AGameHUD::BeginPlay()
{
	AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameData = GameMode->GetGameData();
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		const FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}

	if (MyGameData)
	{
		const int KillCount = MyGameData->EnemyKillCount;
		const FText KillCountText = FText::Format(NSLOCTEXT("Dummy", "Dummy", "Enemies killed: {0}"), KillCount);

		Canvas->DrawText(GEngine->GetMediumFont(), KillCountText, 10.0f, 100.0f, Scale, Scale);
	}
}