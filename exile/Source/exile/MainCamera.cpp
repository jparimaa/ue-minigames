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

	if (!m_movementInput.IsZero())
	{
		m_movementInput = m_movementInput.GetSafeNormal() * 1000.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorRightVector() * m_movementInput.X * DeltaTime;
		NewLocation += GetActorForwardVector() * m_movementInput.Y * DeltaTime;
		NewLocation += GetActorUpVector() * m_movementInput.Z * DeltaTime * m_mouseSensitivity;

		//UE_LOG(LogTemp, Log, TEXT("##### %s"), *m_movementInput.ToString());

		SetActorLocation(NewLocation);
		m_movementInput.Z = 0.0f;
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
	m_movementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::MoveRight(float Value)
{
	m_movementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::MoveUp()
{
	m_movementInput.Z = 1.0f;
}

void AMainCamera::MoveDown()
{
	m_movementInput.Z = -1.0;
}