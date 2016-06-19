// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BTTask_UnsetBlackboardBoolData.h"

// AI module
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_UnsetBlackboardBoolData::UBTTask_UnsetBlackboardBoolData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Unset Blackboard Bool Data";
}

EBTNodeResult::Type UBTTask_UnsetBlackboardBoolData::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	check(BlackboardComp);

	BlackboardComp->SetValueAsBool(GetSelectedBlackboardKey(), false);

	return EBTNodeResult::Succeeded;
}
