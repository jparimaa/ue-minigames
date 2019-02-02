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

