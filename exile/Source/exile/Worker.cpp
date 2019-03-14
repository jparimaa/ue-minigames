#include "Worker.h"

UWorker::UWorker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorker::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("##### UWorker::BeginPlay()"));
}

void UWorker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}
}

void UWorker::setEnabled(bool status)
{
	m_enabled = status;
}

