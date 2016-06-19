// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "HunterCharacter.h"

#include "HunterAIController.h"
#include "RunForLifeCharacter.h"
#include "PreyCharacter.h"

// AI module
#include "Perception/PawnSensingComponent.h"

// Sets default values
AHunterCharacter::AHunterCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set vision angle smaller than other characters
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);

	// Set run speed faster than other characters
	RunSpeed = 700.0f;
	
	// Set as unlimited stamina
	ConsumeStaminaRate = 0.0f;
}

// Called when the game starts or when spawned
void AHunterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add delagates to the sensing component
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AHunterCharacter::OnSeePawn);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AHunterCharacter::OnHearNoise);
	}
}

// Called when seeing a pawn
void AHunterCharacter::OnSeePawn(APawn* Pawn)
{
	AHunterAIController* HunterAIController = Cast<AHunterAIController>(GetController());
	ARunForLifeCharacter* RunForLifeCharacter = Cast<ARunForLifeCharacter>(Pawn);
	APreyCharacter* PreyCharacter = Cast<APreyCharacter>(Pawn);
	
	if (HunterAIController && (RunForLifeCharacter || PreyCharacter))
	{
		HunterAIController->SetPreyLocation(Pawn);
	}
}

// Called when hearing noise
void AHunterCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{	
	AHunterAIController* HunterAIController = Cast<AHunterAIController>(GetController());

	if (HunterAIController && PawnInstigator != this)
	{
		HunterAIController->SetNoiseLocation(Location);
	}
}
