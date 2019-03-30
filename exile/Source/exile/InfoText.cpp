#include "InfoText.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"

AInfoText::AInfoText()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInfoText::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AMainCamera> iter(GetWorld()); iter; ++iter)
	{
		m_mainCamera = *iter;
	}

	m_textRenderComponent = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	check(m_textRenderComponent != nullptr);
	m_textRenderComponent->SetText(FString(""));
}

void AInfoText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator r = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), m_mainCamera->GetActorLocation());
	SetActorRotation(r);
}

void AInfoText::setText(const FString& text)
{
	m_textRenderComponent->SetText(text);
}