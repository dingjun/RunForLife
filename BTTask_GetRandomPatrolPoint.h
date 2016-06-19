// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetRandomPatrolPoint.generated.h"

/**
 * Get Random Patrol Point task node.
 * Get a random patrol target point for NPC character to walk to.
 */
UCLASS()
class RUNFORLIFE_API UBTTask_GetRandomPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

	/** Max distance to get a reachable point from a random patrol target point */
	UPROPERTY(EditAnywhere, Category = Node)
	float SearchRadius;

	UBTTask_GetRandomPatrolPoint(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
