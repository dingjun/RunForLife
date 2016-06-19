// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_Spin.generated.h"

/**
 * Spin task node.
 * Spin at the current location for the specified time when executed.
 */
UCLASS()
class RUNFORLIFE_API UBTTask_Spin : public UBTTask_Wait
{
	GENERATED_BODY()

	/** Spinning direction for one execution */
	int32 SpinningDirection;

	UBTTask_Spin(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
