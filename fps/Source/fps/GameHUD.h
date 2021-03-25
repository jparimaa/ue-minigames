#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameData.h"
#include "Engine/Canvas.h"
#include "GameHUD.generated.h"

UCLASS()
class FPS_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;

private:
	GameData* MyGameData = nullptr;
};
