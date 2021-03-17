// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	*/
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayer::OnFire);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
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
			const FTransform Transform(GetActorLocation() + GetActorForwardVector() * 2.0f + GetActorUpVector());

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
