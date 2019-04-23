#include "Gatherable.h"

namespace
{
const float c_maxYield = 100.0f;
const float c_timeToMaxYield = 30.0f;
const float c_yieldPerSecond = c_maxYield / c_timeToMaxYield;
}

AGatherable::AGatherable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGatherable::BeginPlay()
{
	Super::BeginPlay();
}

void AGatherable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_isFullGrown)
	{
		FVector scale(0.5f + FMath::Lerp(0.0f, 0.5f, m_yield / c_maxYield));
		SetActorScale3D(scale);
		m_yield += DeltaTime * c_yieldPerSecond;
		m_isFullGrown = m_yield > c_maxYield;
	}
}

uint16 AGatherable::gather()
{
	Destroy();
	return static_cast<uint16>(m_yield);
}

void AGatherable::setTargetLock(bool status)
{
	m_targetLocked = status;
}

bool AGatherable::isTargetLocked()
{
	return m_targetLocked;
}