// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BTTask_WalkTo.h"

#include "AIController.h"
#include "BaseCharacter.h"

UBTTask_WalkTo::UBTTask_WalkTo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Walk To";
}

EBTNodeResult::Type UBTTask_WalkTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	check(AIController);

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(AIController->GetCharacter());

	check(BaseCharacter);
	
	// Set up speed for walkning
	BaseCharacter->OnStartWalk();

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
