#pragma once

#include "Components/TextRenderComponent.h"
#include "MainCamera.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfoText.generated.h"

UCLASS()
class EXILE_API AInfoText : public AActor
{
	GENERATED_BODY()

public:
	AInfoText();
	virtual void Tick(float DeltaTime) override;

	void setText(const FString& text);

protected:
	virtual void BeginPlay() override;

private:
	AMainCamera* m_mainCamera = nullptr;
	UTextRenderComponent* m_textRenderComponent = nullptr;
};
