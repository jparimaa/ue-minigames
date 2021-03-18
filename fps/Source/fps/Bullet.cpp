#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	//CollisionComp->BodyInstance.SetCollisionProfileName("Bullet");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	//CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));


	RootComponent = CollisionComp;

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
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Yellow, FString::Printf(TEXT("OnHit: ")) + OtherActor->GetClass()->GetName());

	if (OtherActor->GetClass()->GetName() == FString("EnemyBP_C")) {
		OtherActor->Destroy();
	}

	Destroy();

}