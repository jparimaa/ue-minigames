#include "ConstantDamage.h"
#include "Tower.h"

UConstantDamage::UConstantDamage()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UConstantDamage::BeginPlay()
{
	Super::BeginPlay();
}

void UConstantDamage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ATower* Owner = Cast<ATower>(GetOwner());
	const TArray<AEnemy*>& EnemiesInRange = Owner->GetEnemiesInRange();

	bool IsFiring = false;
	AEnemy* KilledEnemy = nullptr;

	for (int32 i = 0; i < EnemiesInRange.Num(); ++i)
	{
		check(EnemiesInRange[i]->IsAlive());

		IsFiring = true;

		const auto Now = std::chrono::system_clock::now();
		if (Now - LastFiringTime > std::chrono::milliseconds(FiringRateMS)) {
			LastFiringTime = Now;
			AEnemy* Enemy = EnemiesInRange[i];
			Enemy->Damage(Damage);
			if (!Enemy->IsAlive()) {
				KilledEnemy = Enemy;
			}
		}
		break;
	}

	if (KilledEnemy)
	{
		Owner->RemoveEnemyFromRange(KilledEnemy);
	}

	Owner->SetIsFiring(IsFiring);
}

