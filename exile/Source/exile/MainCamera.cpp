#include "MainCamera.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RTSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RTSCamera"));
	RTSCameraComponent->SetupAttachment(RootComponent);
	RTSCameraComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	SetActorLocation(FVector(0.0f, 0.0f, 1000.0f));
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
		NewLocation += GetActorUpVector() * MovementInput.Z * DeltaTime * MouseSensitivity;

		//UE_LOG(LogTemp, Log, TEXT("##### %s"), *MovementInput.ToString());

		SetActorLocation(NewLocation);
		MovementInput.Z = 0.0f;
	}
}

void AMainCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCamera::MoveRight);
	PlayerInputComponent->BindAction("MoveUp", IE_Released, this, &AMainCamera::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Released, this, &AMainCamera::MoveDown);

}

void AMainCamera::MoveForward(float Value)
{
	MovementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::MoveRight(float Value)
{
	MovementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::MoveUp()
{
	MovementInput.Z = 1.0f;
}

void AMainCamera::MoveDown()
{
	MovementInput.Z = -1.0;
}