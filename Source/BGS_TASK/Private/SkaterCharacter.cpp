// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGS_TASK/Public/SkaterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASkaterCharacter::ASkaterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

UCharacterMovementComponent* ASkaterCharacter::GetCharacterMovementComponent_Implementation()
{
	return GetCharacterMovement();
}

float ASkaterCharacter::GetMovementInput_Implementation()
{
	return MovementValue;
}

float ASkaterCharacter::GetTurnInput_Implementation()
{
	return TurnValue;
}

void ASkaterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASkaterCharacter::Jump);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkaterCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASkaterCharacter::StopMove);

		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASkaterCharacter::Turn);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkaterCharacter::Look);
	}
}

void ASkaterCharacter::Move(const FInputActionValue& Value)
{
	MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		MoveForwardValue = FMath::Lerp(MoveForwardValue, MovementValue, .01f);

		if (MovementValue > 0 && !GetCharacterMovement()->IsFalling())
			AddMovementInput(SkateMesh->GetRightVector(), MoveForwardValue);
	}
}

void ASkaterCharacter::StopMove(const FInputActionValue& Value)
{
	MovementValue = 0;
}

void ASkaterCharacter::Jump(const FInputActionValue& Value)
{
	ACharacter::Jump();
	if (!GetCharacterMovement()->IsFalling())
		PlayAnimMontage(JumpMontage, 1.5);
}

void ASkaterCharacter::Turn(const FInputActionValue& Value)
{
	TurnValue = Value.Get<float>();

	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->RotationRate = {0, 350, 0};
	}
	else
	{
		GetCharacterMovement()->RotationRate = {0, 150, 0};
	}

	if (Controller != nullptr)
	{
		const float TurnReduction = 0.02f;
		AddMovementInput(SkateMesh->GetForwardVector() * -1, TurnValue * TurnReduction);
	}
}

void ASkaterCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
