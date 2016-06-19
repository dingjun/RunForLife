// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_WalkTo.generated.h"

/**
 * Walk To task node.
 * Walk toward the specified Actor or Location blackboard entry using the navigation system.
 */
UCLASS()
class RUNFORLIFE_API UBTTask_WalkTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	UBTTask_WalkTo(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
