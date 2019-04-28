#include "House.h"
#include "Classes/Components/SphereComponent.h"

AHouse::AHouse()
{
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
	USphereComponent* sphereComponent = Cast<USphereComponent>(GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OnOverlapBegin);
	sphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABuilding::OnOverlapEnd);
}

void AHouse::onBuildingReady()
{
	setMaterial(m_inGameMaterial);

	FVector location = GetActorLocation();
	location.X += 200.0f;
	FTransform transform(location);
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor(m_residentClass, &transform, spawnParameters);
	Cast<AMyGameMode>(GetWorld()->GetAuthGameMode())->increaseNumResidents();
}
