#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "GameHUD.generated.h"

UCLASS()
class FPS_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;
};
