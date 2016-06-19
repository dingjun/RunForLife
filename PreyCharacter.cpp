// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "PreyCharacter.h"

#include "PreyAIController.h"
#include "HunterCharacter.h"

// AI module
#include "Perception/PawnSensingComponent.h"

// Sets default values
APreyCharacter::APreyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// Called when the game starts or when spawned
void APreyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add delagates to the sensing component
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &APreyCharacter::OnSeePawn);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &APreyCharacter::OnHearNoise);
	}
}

// Called when seeing a pawn
void APreyCharacter::OnSeePawn(APawn* Pawn)
{
	APreyAIController* PreyAIController = Cast<APreyAIController>(GetController());
	AHunterCharacter* HunterCharacter = Cast<AHunterCharacter>(Pawn);
	
	if (PreyAIController && HunterCharacter)
	{
		PreyAIController->SetHunterLocation(Pawn);
	}
}

// Called when hearing noise
void APreyCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	APreyAIController* PreyAIController = Cast<APreyAIController>(GetController());

	if (PreyAIController && PawnInstigator != this)
	{
		PreyAIController->SetNoiseLocation(Location);
	}
}
