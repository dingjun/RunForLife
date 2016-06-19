// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPCAIController.h"
#include "PreyAIController.generated.h"

/**
 * Prey AI Controller is NPC AI Controller with corresponding actions to run away from hunter.
 */
UCLASS()
class RUNFORLIFE_API APreyAIController : public ANPCAIController
{
	GENERATED_BODY()

public:

	/** Blackboard key names */
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName IsSeeingHunterKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName HunterKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName HunterLocationKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName SafeLocationKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName IsPatrollingKey;

	/** Safe distance from hunter or noise */
	UPROPERTY(EditAnywhere, Category = AI)
	float SafeDistance;

	/** Prey starts to patrol when its stamina becomes greater than PatrollingStamina */
	UPROPERTY(EditAnywhere, Category = AI)
	float PatrollingStamina;
	
	/** Prey starts to rest when its stamina becomes less than RestingStamina */
	UPROPERTY(EditAnywhere, Category = AI)
	float RestingStamina;

	APreyAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;

	/** Called whenever the controller possesses a character */
	virtual void Possess(APawn* InPawn) override;

	void SetHunterLocation(APawn* Prey);

	void SetNoiseLocation(const FVector& Location);

	void SetSafePatrolPoint(const FVector& Location);
};
