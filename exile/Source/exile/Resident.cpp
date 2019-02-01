#include "Resident.h"

AResident::AResident()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResident::BeginPlay()
{
	Super::BeginPlay();

}

void AResident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResident::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

