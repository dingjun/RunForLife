// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCCharacter.h"
#include "HunterCharacter.generated.h"

/**
 * Hunter Character is NPC Character that would go to where target prey or noise is.
 */
UCLASS()
class RUNFORLIFE_API AHunterCharacter : public ANPCCharacter
{
	GENERATED_BODY()

	/** Called when seeing a pawn */
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn) override;

	/** Called when hearing noise */
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume) override;

public:

	/** Sets default values for this character's properties */
	AHunterCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;
};
