#include "MainCamera.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RTSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RTSCamera"));
	RTSCameraComponent->SetupAttachment(RootComponent);
	RTSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 1000.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorRightVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorForwardVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

void AMainCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCamera::MoveRight);

}

void AMainCamera::MoveForward(float Value)
{
	MovementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::MoveRight(float Value)
{
	MovementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}