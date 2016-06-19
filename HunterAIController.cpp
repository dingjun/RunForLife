// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "HunterAIController.h"

#include "HunterCharacter.h"
#include "PatrolTargetPoint.h"

// AI module
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AHunterAIController::AHunterAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set blackboard key names
	IsSeeingPreyKey = "IsSeeingPrey";
	PreyKey = "Prey"; 
	PreyLocationKey = "PreyLocation";

	LastSeenTime = 0.0f;
	SeenExpirationTime = 2.0f;
}

void AHunterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSeconds - LastSeenTime >= SeenExpirationTime)
	{
		BlackboardComp->SetValueAsBool(IsSeeingPreyKey, false);
	}
}

void AHunterAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AHunterCharacter* HunterCharacter = Cast<AHunterCharacter>(InPawn);
	
	if (HunterCharacter && HunterCharacter->BehaviorTree->BlackboardAsset)
	{
		// Initialize blackboard
		BlackboardComp->InitializeBlackboard(*HunterCharacter->BehaviorTree->BlackboardAsset);

		// Start behavior tree
		BehaviorComp->StartTree(*HunterCharacter->BehaviorTree);
	}
		
	// Store all patrol target points
	UGameplayStatics::GetAllActorsOfClass(this, APatrolTargetPoint::StaticClass(), PatrolTargetPoints);
}

void AHunterAIController::SetPreyLocation(APawn* Prey)
{
	if (BlackboardComp && Prey)
	{
		// Unset noise information
		BlackboardComp->SetValueAsBool(IsHearingNoiseKey, false);

		const FVector NewPreyLocation = Prey->GetActorLocation();

		// No prey record or the new prey is closer
		if (!BlackboardComp->GetValueAsBool(IsSeeingPreyKey) || IsNewLocationCloser(NewPreyLocation, PreyLocationKey))
		{
			LastSeenTime = GetWorld()->TimeSeconds;

			// Set prey information
			BlackboardComp->SetValueAsBool(IsSeeingPreyKey, true);
			BlackboardComp->SetValueAsObject(PreyKey, Prey);
			BlackboardComp->SetValueAsVector(PreyLocationKey, NewPreyLocation);
		}
	}
}

void AHunterAIController::SetNoiseLocation(const FVector& Location)
{
	if (BlackboardComp)
	{
		// Not seeing a prey
		if (!BlackboardComp->GetValueAsBool(IsSeeingPreyKey))
		{
			// No noise record or the new noise is closer
			if (!BlackboardComp->GetValueAsBool(IsHearingNoiseKey) || IsNewLocationCloser(Location, NoiseLocationKey))
			{
				// Set noise information
				BlackboardComp->SetValueAsBool(IsHearingNoiseKey, true);
				BlackboardComp->SetValueAsVector(NoiseLocationKey, Location);
			}
		}
	}
}
