#include "BuildingSpawner.h"
#include "MainCamera.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

ABuildingSpawner::ABuildingSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AMainCamera> iter(GetWorld()); iter; ++iter)
	{
		m_mainCamera = Cast<UCameraComponent>(iter->GetComponentByClass(UCameraComponent::StaticClass()));
	}
	check(m_mainCamera != nullptr);

	for (TActorIterator<APlayerController> iter(GetWorld()); iter; ++iter)
	{
		m_playerController = *iter;
	}
	check(m_playerController != nullptr);
}

void ABuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = m_mainCamera->GetComponentLocation() + FVector(0.0f, 0.0f, 10.0f);

	FVector mouseLocation, mouseDirection;
	m_playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FVector end = ((mouseDirection * 10000.f) + start);
	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 10.0f, 0, 1.0f);

	FHitResult outHit;
	if (GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, CollisionParams))
	{
		if (outHit.bBlockingHit)
		{

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *outHit.GetActor()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *outHit.ImpactPoint.ToString()));
		}
	}
}

