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

	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* component : components)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(component);
		check(staticMesh != nullptr);
		m_originalMaterials.Add(staticMesh->GetMaterial(0));
	}
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
	UE_LOG(LogTemp, Log, TEXT("ABuilding::OnOverlapBegin: OtherActor is %s"), *OtherActor->GetName());

	if (OtherActor->GetName() == FString("Floor"))
	{
		return;
	}

	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* component : components)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(component);
		check(staticMesh != nullptr);
		staticMesh->SetMaterial(0, m_unableToBuildMaterial);
	}
}

void ABuilding::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());

	check(components.Num() > 0);
	UStaticMeshComponent* firstStaticMesh = Cast<UStaticMeshComponent>(components[0]);
	if (firstStaticMesh->GetMaterial(0) == m_unableToBuildMaterial)
	{
		for (int32 i = 0; i < components.Num(); ++i)
		{
			UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(components[i]);
			check(staticMesh != nullptr);
			staticMesh->SetMaterial(0, m_originalMaterials[i]);
		}
	}
}