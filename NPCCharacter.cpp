// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "NPCCharacter.h"

// AI module
#include "Perception/PawnSensingComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	// Set up sensing component
	if (PawnSensingComp)
	{
		PawnSensingComp->SetPeripheralVisionAngle(120.0f);
		PawnSensingComp->SightRadius = 2000.0f;
		PawnSensingComp->HearingThreshold = 600.0f;
		PawnSensingComp->LOSHearingThreshold = 1200.0f;
		PawnSensingComp->bOnlySensePlayers = false;
	}

	SpinSpeed = 100.0f;
}
