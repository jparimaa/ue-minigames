#include "Bullet.h"
#include "Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphereComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphereComp"));
	SphereComp->InitSphereRadius(50.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	SphereComp->SetupAttachment(RootComponent);



	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->InitialSpeed = 3000.0f;
	ProjectileMovementComp->MaxSpeed = 3000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = true;
	ProjectileMovementComp->Bounciness = 0.3f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->GetName() == FString("Enemy_BP_C")) {
		Destroy();
	}
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->GetName() == FString("Enemy_BP_C")) {
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		Enemy->Kill();
	}
}