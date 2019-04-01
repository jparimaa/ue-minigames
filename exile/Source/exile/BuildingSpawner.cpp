#include "BuildingSpawner.h"
#include "House.h"
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

	EnableInput(GetWorld()->GetFirstPlayerController());
	UInputComponent* inputComponent = this->InputComponent;
	if (inputComponent)
	{
		setupInputComponent(inputComponent);
	}

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

	if (m_placing)
	{
		FVector start = m_mainCamera->GetComponentLocation() + FVector(0.0f, 0.0f, 10.0f);

		FVector mouseLocation, mouseDirection;
		m_playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		FVector end = ((mouseDirection * 10000.f) + start);
		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(m_currentBuilding);

		//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f, 0, 1.0f);

		FHitResult outHit;
		if (GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams))
		{
			if (outHit.bBlockingHit && *outHit.GetActor()->GetName() == FString("Floor"))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *outHit.GetActor()->GetName()));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *outHit.ImpactPoint.ToString()));

				FVector actorLocation(outHit.ImpactPoint.X, outHit.ImpactPoint.Y, 0.0f);
				m_currentBuilding->SetActorLocation(outHit.ImpactPoint);
			}
		}
	}
}

void ABuildingSpawner::placeBuilding(int type)
{
	m_placing = true;

	FActorSpawnParameters spawnParameters;
	FTransform transform(FVector(0.0f, 0.0f, 99999.0f));
	m_currentBuilding = (ABuilding*)GetWorld()->SpawnActor(m_houseClass, &transform, spawnParameters);
	check(m_currentBuilding != nullptr);
	m_currentBuilding->setStatus(ABuilding::Status::Placing);
	m_currentBuilding->setType(ABuilding::Type::House);
}

void ABuildingSpawner::setupInputComponent(UInputComponent* myInputComponent)
{
	myInputComponent->BindAction("SpawnBuilding", IE_Released, this, &ABuildingSpawner::spawnBuilding);
}

void ABuildingSpawner::spawnBuilding()
{
	if (m_placing && m_currentBuilding->allowPlacing())
	{
		m_currentBuilding->setStatus(ABuilding::Status::Constructing);
		m_currentBuilding->setProgressText(FString("0 %"));
		m_placing = false;
	}
}
