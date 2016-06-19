// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

/**
 * Base Character is Character that has stamina and run/walk logic.
 */
UCLASS(Abstract)
class RUNFORLIFE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Maximum allowed difference for comparing two speed squared */
	const float SpeedSquaredErrorTolerance = 4.0f;

	/** Time interval to update speed and stamina */
	const float UpdateTimeInterval = 0.1f;
	
	/** Component emits noise while character running */
	UPawnNoiseEmitterComponent* NoiseEmitterComp;

	/** Whether character is running, may not exactly be running while stamina is not enough */
	bool bIsRunning;

	/** Handle to manage the timer for updating speed and stamina */
	FTimerHandle UpdateTimerHandle;

	/** Called to update speed and stamina */
	void Update();

protected:

	/** Max speed for running */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float RunSpeed;
	
	/** Max speed for walking */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float WalkSpeed;
	
	/** Max stamina */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float MaxStamina;

	/** Current stamina */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float CurrentStamina;

	/** Rate for consuming stamina while running */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float ConsumeStaminaRate;

	/** Rate for recovering stamina while not walking or running */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float RecoverStaminaRate;

public:

	/** Sets default values for this character's properties */
	ABaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
	/** Called when the game ends or when destroyed */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnStartRun();

	void OnStartWalk();

	/** Returns maximum stamina */
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	/** Returns current stamina */
	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }
};
