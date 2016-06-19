// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "PreyAIController.h"

#include "PreyCharacter.h"
#include "PatrolTargetPoint.h"

// AI module
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APreyAIController::APreyAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set blackboard key names
	IsSeeingHunterKey = "IsSeeingHunter";
	HunterKey = "Hunter";
	HunterLocationKey = "HunterLocation";
	SafeLocationKey = "SafeLocation";
	IsPatrollingKey = "IsPatrolling";

	SafeDistance = 700.0f;
	PatrollingStamina = 70.0f;
	RestingStamina = 30.0f;
}

void APreyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APreyCharacter* PreyCharacter = Cast<APreyCharacter>(GetPawn());

	if (PreyCharacter && BlackboardComp)
	{
		if (PreyCharacter->GetCurrentStamina() > PatrollingStamina)
		{
			BlackboardComp->SetValueAsBool(IsPatrollingKey, true);
		}
		else if (PreyCharacter->GetCurrentStamina() < RestingStamina)
		{
			BlackboardComp->SetValueAsBool(IsPatrollingKey, false);
		}
	}
}

void APreyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	APreyCharacter* PreyCharacter = Cast<APreyCharacter>(InPawn);

	if (PreyCharacter && PreyCharacter->BehaviorTree->BlackboardAsset)
	{
		// Initialize blackboard
		BlackboardComp->InitializeBlackboard(*PreyCharacter->BehaviorTree->BlackboardAsset);

		// Start behavior tree
		BehaviorComp->StartTree(*PreyCharacter->BehaviorTree);
	}

	// Store all patrol target points
	UGameplayStatics::GetAllActorsOfClass(this, APatrolTargetPoint::StaticClass(), PatrolTargetPoints);
}

void APreyAIController::SetHunterLocation(APawn* Hunter)
{
	if (BlackboardComp && Hunter)
	{
		// Unset noise information
		BlackboardComp->SetValueAsBool(IsHearingNoiseKey, false);

		const FVector NewHunterLocation = Hunter->GetActorLocation();

		// No hunter record or the new hunter is closer
		if (!BlackboardComp->GetValueAsBool(IsSeeingHunterKey) || IsNewLocationCloser(NewHunterLocation, HunterLocationKey))
		{
			// Set hunter information
			BlackboardComp->SetValueAsBool(IsSeeingHunterKey, true);
			BlackboardComp->SetValueAsVector(HunterLocationKey, NewHunterLocation);

			SetSafePatrolPoint(NewHunterLocation);
		}
	}
}

void APreyAIController::SetNoiseLocation(const FVector& Location)
{
	if (BlackboardComp)
	{
		// Not seeing a hunter
		if (!BlackboardComp->GetValueAsBool(IsSeeingHunterKey))
		{
			// No noise record or the new noise is closer
			if (!BlackboardComp->GetValueAsBool(IsHearingNoiseKey) || IsNewLocationCloser(Location, NoiseLocationKey))
			{
				// Set noise information
				BlackboardComp->SetValueAsBool(IsHearingNoiseKey, true);
				BlackboardComp->SetValueAsVector(NoiseLocationKey, Location);

				SetSafePatrolPoint(Location);
			}
			// Noise is closer implies hunter might chase after prey itself
			else if (IsNewLocationCloser(Location, NoiseLocationKey))
			{
				BlackboardComp->SetValueAsBool(IsHearingNoiseKey, false);
				BlackboardComp->SetValueAsBool(IsSeeingHunterKey, true);
				BlackboardComp->SetValueAsVector(HunterLocationKey, Location);

				SetSafePatrolPoint(Location);
			}
		}
	}
}

void APreyAIController::SetSafePatrolPoint(const FVector& UnsafeLocation)
{
	if (BlackboardComp && GetCharacter() && PatrolTargetPoints.Num() > 0)
	{
		const FVector ActorLocation = GetCharacter()->GetActorLocation();
		const FVector UnsafeDirection = UnsafeLocation - ActorLocation;

		float MaxDistanceSquared = 0.0f;
		
		// Find a random patrol target point as a starting point for searching safe location
		const int32 RandomIndex = FMath::RandRange(0, PatrolTargetPoints.Num() - 1);
		int Index = RandomIndex;
		int FarthestIndex = Index;
		
		do
		{
			Index = (Index + 1) % PatrolTargetPoints.Num();

			const FVector CandidateLocation = PatrolTargetPoints[Index]->GetActorLocation();
			const FVector CandidateDirection = CandidateLocation - ActorLocation;

			const float SafeDistanceSquared = SafeDistance * SafeDistance;
			const float DistanceSquared = FVector::DistSquaredXY(CandidateLocation, UnsafeLocation);

			// Update FarthestIndex if CandidateLocation has the maximum distance from UnsafeLocation
			FarthestIndex = (DistanceSquared > MaxDistanceSquared) ? Index : FarthestIndex;

			// Check if the distance between CandidateLocation and UnsafeLocation is safe enough
			// and the angle between UnsafeDirection and CandidateDirection is larger than or equal to 90 degrees
			if (DistanceSquared >= SafeDistanceSquared && UnsafeDirection.CosineAngle2D(CandidateDirection) <= 0.0f)
			{
				// Set the candidate location as safe locaiton and stop searching
				BlackboardComp->SetValueAsVector(SafeLocationKey, CandidateLocation);
				return;
			}
		} while (Index != RandomIndex);

		// Set the farthest partol target point from UnsafeLocation as safe location
		BlackboardComp->SetValueAsVector(SafeLocationKey, PatrolTargetPoints[FarthestIndex]->GetActorLocation());
	}
}
