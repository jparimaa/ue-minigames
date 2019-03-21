#include "Worker.h"

UWorker::UWorker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorker::BeginPlay()
{
	Super::BeginPlay();
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

