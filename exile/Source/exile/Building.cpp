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

	FActorSpawnParameters spawnParameters;
	FTransform transform(FVector(0.0f, 0.0f, 150.0f));
	m_infoText = (AInfoText*)GetWorld()->SpawnActor(m_infoTextClass, &transform, spawnParameters);
	check(m_infoText != nullptr);
	m_infoText->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::setStatus(Status status)
{
	m_status = status;
	if (status == Status::Placing)
	{
		setMaterial(m_buildInProcessMaterial);
		setCollision(ECollisionEnabled::NoCollision);
	}
	else if (status == Status::Constructing)
	{
		setCollision(ECollisionEnabled::QueryAndPhysics);
	}
}

ABuilding::Status ABuilding::getStatus()
{
	return m_status;
}

void ABuilding::setProgressText(const FString& text)
{
	m_infoText->setText(text);
}

bool ABuilding::allowPlacing()
{
	return m_allowPlacing;
}

void ABuilding::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("ABuilding::OnOverlapBegin: OtherActor is %s"), *OtherActor->GetName());

	if (OtherActor->GetName() == FString("Floor") || OtherActor == this || m_status != Status::Placing)
	{
		return;
	}

	setMaterial(m_unableToBuildMaterial);
	m_allowPlacing = false;
}

void ABuilding::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (m_status != Status::Placing)
	{
		return;
	}

	setMaterial(m_buildInProcessMaterial);
	m_allowPlacing = true;
}

void ABuilding::setMaterial(UMaterialInterface* material)
{
	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* component : components)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(component);
		check(staticMesh != nullptr);
		staticMesh->SetMaterial(0, material);
	}
}

void ABuilding::setCollision(ECollisionEnabled::Type collision)
{
	TArray<UActorComponent*> components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* component : components)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(component);
		check(staticMesh != nullptr);
		staticMesh->SetCollisionEnabled(collision);
	}
}