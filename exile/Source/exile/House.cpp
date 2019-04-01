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
