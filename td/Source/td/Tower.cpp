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

	IsFiring = false;

	for (int32 i = 0; i < EnemiesInRange.Num(); ++i)
	{
		if (!EnemiesInRange[i]->IsAlive()) {
			continue;
		}

		IsFiring = true;

		const auto Now = std::chrono::system_clock::now();
		if (Now - LastFiringTime > std::chrono::milliseconds(FiringRateMS)) {
			LastFiringTime = Now;
			AEnemy* Enemy = EnemiesInRange[i];
			Enemy->Damage(Damage);
			if (!Enemy->IsAlive()) {
				EnemiesInRange.RemoveSingle(Enemy);
			}
		}
		break;
	}
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