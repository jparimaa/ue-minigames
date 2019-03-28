#pragma once

#include "Components/TextRenderComponent.h"
#include "MainCamera.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingProgress.generated.h"

UCLASS()
class EXILE_API ABuildingProgress : public AActor
{
	GENERATED_BODY()

public:
	ABuildingProgress();
	virtual void Tick(float DeltaTime) override;

	void setText(const FString& text);

protected:
	virtual void BeginPlay() override;

private:
	AMainCamera* m_mainCamera = nullptr;
	UTextRenderComponent* m_textRenderComponent = nullptr;
};
