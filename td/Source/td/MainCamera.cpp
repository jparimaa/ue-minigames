#include "MainCamera.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator NewRotation = FRotator(0.0f, YawValue, 0.0f);
	const FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
	YawValue = 0.0f;

	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 1000.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorRightVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorForwardVector() * MovementInput.Y * DeltaTime;
		NewLocation += GetActorUpVector() * MovementInput.Z * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

void AMainCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCamera::MoveRight);
	PlayerInputComponent->BindAxis("RotateRight", this, &AMainCamera::RotateRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &AMainCamera::MoveUp);
}

void AMainCamera::MoveForward(float Value)
{
	MovementInput.Y = Value;
}

void AMainCamera::MoveRight(float Value)
{
	MovementInput.X = Value;
}

void AMainCamera::MoveUp(float Value)
{
	MovementInput.Z = Value;
}

void AMainCamera::RotateRight(float Value)
{
	YawValue += Value;
}