// Fill out your copyright notice in the Description page of Project Settings.


#include "BunnyDetective.h"

#include "ParticleHelper.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABunnyDetective::ABunnyDetective()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bunny"));
	playerModel->SetupAttachment(RootComponent);

	turner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turn"));
	turner->SetupAttachment(RootComponent);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(turner);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	cameraRot = 270;
}

// Called when the game starts or when spawned
void ABunnyDetective::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABunnyDetective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABunnyDetective::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABunnyDetective::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABunnyDetective::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &ACharacterMovement::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABunnyDetective::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABunnyDetective::StopJump);

}


void ABunnyDetective::MoveForward(float Value)
{
	FVector Direction;
	if (cameraRot == 180 || cameraRot == 270)
	{
		if (Value == 1)
		{
			Value = -1;
		}
		else if (Value == - 1)
		{
			Value = 1;
		}
	}
	if (cameraRot == 90 || cameraRot == 270)
	{
		Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	}
	else
	{
		Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	}
	AddMovementInput(Direction, Value);
}

void ABunnyDetective::MoveRight(float Value)
{
	FVector Direction;
	if (cameraRot == 90 || cameraRot == 180)
	{
		if (Value == 1)
		{
			Value = -1;
		}
		else if (Value == -1)
		{
			Value = 1;
		}
	}
	if (cameraRot == 90 || cameraRot == 270)
	{
		Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	}
	else
	{
		Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	}
	AddMovementInput(Direction, Value);
}

void ABunnyDetective::StartJump()
{
	bPressedJump = true;
}

void ABunnyDetective::StopJump()
{
	bPressedJump = false;
}


