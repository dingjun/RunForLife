// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCAIController.h"
#include "HunterAIController.generated.h"

/**
 * Hunter AI Controller is NPC AI Controller with corresponding actions to pursue prey.
 */
UCLASS()
class RUNFORLIFE_API AHunterAIController : public ANPCAIController
{
	GENERATED_BODY()

	/** Last time seeing prey */
	float LastSeenTime;

	/** Period of time seen target expires */
	UPROPERTY(EditAnywhere, Category = AI)
	float SeenExpirationTime;

public:

	/** Blackboard key names */
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName IsSeeingPreyKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName PreyKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName PreyLocationKey;

	AHunterAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;

	/** Called whenever the controller possesses a character */
	virtual void Possess(APawn* InPawn) override;

	void SetPreyLocation(APawn* Prey);

	void SetNoiseLocation(const FVector& Location);
};
