#include "SplashDamage.h"
#include "Tower.h"
#include "Enemy.h"
#include "EngineUtils.h"

USplashDamage::USplashDamage()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USplashDamage::BeginPlay()
{
	Super::BeginPlay();
}

void USplashDamage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ATower* Owner = Cast<ATower>(GetOwner());

	const TArray<AEnemy*>& EnemiesInRange = Owner->GetEnemiesInRange();
	if (EnemiesInRange.Num() == 0) {
		Owner->SetIsFiring(false);
		return;
	}

	Owner->SetIsFiring(true);

	const auto Now = std::chrono::system_clock::now();
	if (Now - LastFiringTime < std::chrono::milliseconds(FiringRateMS)) {
		return;
	}

	LastFiringTime = Now;
	AEnemy* TargetEnemy = EnemiesInRange[0];
	check(TargetEnemy->IsAlive());

	TArray<AEnemy*> EnemiesInSplashRadius;
	TArray<AEnemy*> KilledEnemies;

	for (TActorIterator<AEnemy> iter(GetWorld()); iter; ++iter)
	{
		const int Distance = static_cast<int>(iter->GetDistanceTo(Cast<AActor>(TargetEnemy)));
		if (Distance < SplashRadius) {
			iter->Damage(Damage);
			if (!iter->IsAlive()) {
				KilledEnemies.Add(*iter);
			}
		}
	}

	for (int32_t i = 0; i < KilledEnemies.Num(); ++i)
	{
		Owner->RemoveEnemyFromRange(KilledEnemies[i]);
	}
}

