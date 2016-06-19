// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UnsetBlackboardBoolData.generated.h"

/**
 * Unset Blackboard Bool Data task node.
 * Set a blackboard bool data as false.
 */
UCLASS()
class RUNFORLIFE_API UBTTask_UnsetBlackboardBoolData : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTask_UnsetBlackboardBoolData(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
