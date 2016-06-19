// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_RunTo.generated.h"

/**
 * Run To task node.
 * Run toward the specified Actor or Location blackboard entry using the navigation system.
 */
UCLASS()
class RUNFORLIFE_API UBTTask_RunTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	UBTTask_RunTo(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
