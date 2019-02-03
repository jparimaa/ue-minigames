#include "Tree.h"

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
}

bool ATree::cut(uint16 damage, uint16& yield)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		yield = m_yield;
		Destroy();
		return true;
	}
	yield = 0;
	return false;
}