// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "NPCAIController.generated.h"

/**
 * NPC AI Controller is AI Controller with behavior tree and blackboard components.
 */
UCLASS(Abstract)
class RUNFORLIFE_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	/** Behavior tree component */
	UBehaviorTreeComponent* BehaviorComp;

	/** Blackboard component */
	UBlackboardComponent* BlackboardComp;

	/** Target points for patrol */
	TArray<AActor*> PatrolTargetPoints;

public:

	/** Blackboard key names */
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName IsHearingNoiseKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName NoiseLocationKey;
	UPROPERTY(VisibleAnywhere, Category = AI)
	FName PatrolLocationKey;

	ANPCAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	bool IsNewLocationCloser(const FVector& NewKeyLocation, const FName& Key);

	/** Returns behavior tree component */
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	/** Returns blackboard component */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	
	/** Returns patrol target points */
	FORCEINLINE TArray<AActor*> GetPatrolTargetPoints() const { return PatrolTargetPoints; }
};
