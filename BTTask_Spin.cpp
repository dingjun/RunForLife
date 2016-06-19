// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BTTask_Spin.h"

#include "AIController.h"
#include "NPCCharacter.h"

UBTTask_Spin::UBTTask_Spin(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Spin";
	WaitTime = 3.0f;
	RandomDeviation = 2.0f;
}

EBTNodeResult::Type UBTTask_Spin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Set up a random spinning direction
	SpinningDirection = (FMath::RandRange(0, 1) == 0) ? -1 : 1;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_Spin::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	check(AIController);

	ANPCCharacter* NPCCharacter = Cast<ANPCCharacter>(AIController->GetCharacter());

	check(NPCCharacter);

	// Rotate NPC character
	FRotator Rotator = NPCCharacter->GetActorRotation();
	Rotator.Yaw += SpinningDirection * NPCCharacter->GetSpinSpeed() * DeltaSeconds;
	NPCCharacter->SetActorRotation(Rotator);

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
