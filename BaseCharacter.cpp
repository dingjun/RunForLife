// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BaseCharacter.h"

// AI module
#include "Components/PawnNoiseEmitterComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create noise emitter component
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComp"));

	// Set default speed and stamina
	RunSpeed = 600.0f;
	WalkSpeed = 200.0f;
	MaxStamina = 100.0f;
	CurrentStamina = 100.0f;
	ConsumeStaminaRate = 1.0f;		// per UpdateTimeInterval(0.1) second
	RecoverStaminaRate = 1.0f;		// per UpdateTimeInterval(0.1) second

	// Set default max speed as walk speed
	bIsRunning = false;

	// Set default collision capsule size
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set an infinite-loop timer to update speed and stamina
	GetWorldTimerManager().SetTimer(UpdateTimerHandle, this, &ABaseCharacter::Update, UpdateTimeInterval, true);
}

// Called when the game ends or when destroyed
void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Clear timer
	GetWorldTimerManager().ClearTimer(UpdateTimerHandle);
}

void ABaseCharacter::Update()
{
	// Update max speed
	if (bIsRunning && CurrentStamina >= ConsumeStaminaRate)
	{
		// Set max speed for running
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
	else
	{
		// Set max speed for walking
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	float WalkSpeedSquared = WalkSpeed * WalkSpeed;
	float CurrentSpeedSquared = GetVelocity().SizeSquared();

	// Update stamina
	if (CurrentSpeedSquared == 0)
	{
		// Increase stamina without overflow while not walking or running
		CurrentStamina = (CurrentStamina + RecoverStaminaRate < MaxStamina) ? CurrentStamina + RecoverStaminaRate : MaxStamina;
	}
	else if (CurrentSpeedSquared > WalkSpeedSquared + SpeedSquaredErrorTolerance)
	{
		// Make noise
		MakeNoise(1.0f);

		// Decrease stamina without underflow while running
		CurrentStamina = (CurrentStamina - ConsumeStaminaRate > 0) ? CurrentStamina - ConsumeStaminaRate : 0;
	}
}

void ABaseCharacter::OnStartRun()
{
	bIsRunning = true;
}

void ABaseCharacter::OnStartWalk()
{
	bIsRunning = false;
}
