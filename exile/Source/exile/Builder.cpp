#include "Builder.h"

UBuilder::UBuilder()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuilder::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("##### UBuilder::BeginPlay()"));
}

void UBuilder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}
}

void UBuilder::setEnabled(bool status)
{
	m_enabled = status;
}

