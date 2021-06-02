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

	TargetEnemy->Damage(Damage);
	if (!TargetEnemy->IsAlive()) {
		Owner->RemoveEnemyFromRange(TargetEnemy);
	}
}

