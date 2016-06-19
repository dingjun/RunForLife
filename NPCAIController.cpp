// Fill out your copyright notice in the Description page of Project Settings.

#include "RunForLife.h"
#include "NPCAIController.h"

// AI module
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ANPCAIController::ANPCAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create behavior tree and blackboard components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Set blackboard key names
	IsHearingNoiseKey = "IsHearingNoise";
	NoiseLocationKey = "NoiseLocation";
	PatrolLocationKey = "PatrolLocation";
}

bool ANPCAIController::IsNewLocationCloser(const FVector& NewKeyLocation, const FName& Key)
{
	if (BlackboardComp && GetCharacter())
	{
		const FVector CurrentKeyLocation = BlackboardComp->GetValueAsVector(Key);
		const FVector ActorLocation = GetCharacter()->GetActorLocation();

		return (FVector::DistSquaredXY(NewKeyLocation, ActorLocation) < FVector::DistSquaredXY(CurrentKeyLocation, ActorLocation));
	}

	return false;
}
