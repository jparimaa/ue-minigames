// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMainPlayer::AMainPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 80.0f));
	CameraComponent->bUsePawnControlRotation = true;
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayer::OnFire);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Horizontal", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Vertical", this, &APawn::AddControllerPitchInput);
}

void AMainPlayer::OnFire()
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (BulletClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FVector Position = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 25.0f - CameraComponent->GetUpVector() * 15.0f;
			const FTransform Transform(GetControlRotation(), Position, FVector(1.0f, 1.0f, 1.0f));

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<ABullet>(BulletClass, Transform, ActorSpawnParams);
		}
	}
}

void AMainPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("MoveForward %f"), Value));
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMainPlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("MoveRight %f"), Value));
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMainPlayer::StartJump()
{
	bPressedJump = true;
}

void AMainPlayer::StopJump()
{
	bPressedJump = false;
}