#include "Tower.h"
#include "Enemy.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RangeComp"));
	SphereComp->InitSphereRadius(1000.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlapBegin);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ATower::OnOverlapEnd);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATower::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy entered range"));
	}
}

void ATower::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy left range"));
	}
}