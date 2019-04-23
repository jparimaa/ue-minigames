#include "Gatherer.h"
#include "Resident.h"
#include "Classes/Components/SphereComponent.h"

UGatherer::UGatherer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGatherer::BeginPlay()
{
	Super::BeginPlay();

	m_owner = Cast<AResident>(GetOwner());

	USphereComponent* sphereComponent = Cast<USphereComponent>(m_owner->GetDefaultSubobjectByName(TEXT("Sphere")));
	check(sphereComponent != nullptr);
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UGatherer::OnOverlapBegin);
}

void UGatherer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_enabled)
	{
		return;
	}

	//UE_LOG(LogTemp, Log, TEXT("##### UGatherer::TickComponent"));

	if (m_status == Status::WaitingForGatherable)
	{
	}

	if (m_status == Status::WalkingToGatherable)
	{
	}

	if (m_status == Status::Gathering)
	{
	}

	if (m_status == Status::ReturningGatherable)
	{
	}
}

void UGatherer::setEnabled(bool status)
{
	m_enabled = status;
}

void UGatherer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
}