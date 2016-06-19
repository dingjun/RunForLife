// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "BTTask_GetRandomPatrolPoint.h"

#include "NPCAIController.h"

// AI module
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomPatrolPoint::UBTTask_GetRandomPatrolPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Get Random Patrol Point";
	SearchRadius = 100.0f;
}

EBTNodeResult::Type UBTTask_GetRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIController* NPCAIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	check(NPCAIController && BlackboardComp);
	
	const TArray<AActor*> PatrolTargetPoints = NPCAIController->GetPatrolTargetPoints();

	if (PatrolTargetPoints.Num() > 0)
	{
		// Find a random location that is close to a random patrol target point
		const int32 RandomIndex = FMath::RandRange(0, PatrolTargetPoints.Num() - 1);
		const FVector SearchOrigin = PatrolTargetPoints[RandomIndex]->GetActorLocation();
		const FVector RandomLocation = UNavigationSystem::GetRandomReachablePointInRadius(NPCAIController, SearchOrigin, SearchRadius);

		BlackboardComp->SetValueAsVector(NPCAIController->PatrolLocationKey, RandomLocation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
