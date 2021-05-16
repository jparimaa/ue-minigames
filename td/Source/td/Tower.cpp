#include "Tower.h"

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
		EnemiesInRange.Add(Cast<AEnemy>(OtherActor));
	}
}

void ATower::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		EnemiesInRange.RemoveSingle(Cast<AEnemy>(OtherActor));
	}
}

const TArray<AEnemy*>& ATower::GetEnemiesInRange() const
{
	return EnemiesInRange;
}

void ATower::RemoveEnemyFromRange(AEnemy* Enemy)
{
	EnemiesInRange.RemoveSingle(Enemy);
}

void ATower::SetIsFiring(bool Status)
{
	IsFiring = Status;
}