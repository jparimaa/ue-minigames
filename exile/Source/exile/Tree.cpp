#include "Tree.h"

namespace
{
const float c_maxYield = 100.0f;
const float c_timeToMaxYield = 30.0f;
const float c_yieldPerSecond = c_maxYield / c_timeToMaxYield;
}

ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATree::BeginPlay()
{
	Super::BeginPlay();
}

void ATree::Tick(float DeltaTime)
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

bool ATree::cut(uint16 damage, uint16& yield)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		yield = getYield();
		Destroy();
		return true;
	}
	yield = 0;
	return false;
}

uint16_t ATree::getYield()
{
	return static_cast<uint16_t>(m_yield);
}

bool ATree::isFullGrown()
{
	return m_isFullGrown;
}
