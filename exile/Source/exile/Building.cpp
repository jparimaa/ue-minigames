#include "Building.h"
#include "Classes/Engine/StaticMesh.h"
#include "EngineUtils.h"
#include "Engine.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::setStatus(Status status)
{
	m_status = status;
}

ABuilding::Status ABuilding::getStatus()
{
	return m_status;
}


void ABuilding::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->GetName() == FString("Floor"))
	{
		return;
	}

	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Num Comps: %i"), components.Num()));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Num Comps: %s"), *GetClass()->GetFName().ToString()));

	for (UActorComponent* component : components)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(component);
		check(staticMesh != nullptr);
		staticMesh->SetMaterial(0, unableToBuildMaterial);
	}

}