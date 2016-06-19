// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BTTask_RunTo.h"

#include "AIController.h"
#include "BaseCharacter.h"

UBTTask_RunTo::UBTTask_RunTo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Run To";
}

EBTNodeResult::Type UBTTask_RunTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	check(AIController);

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(AIController->GetCharacter());

	check(BaseCharacter);

	// Set up speed for running
	BaseCharacter->OnStartRun();

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
