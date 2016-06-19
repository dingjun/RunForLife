// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "NPCCharacter.generated.h"

/**
 * NPC Character is Base Character that has sensing component and behavior tree.
 */
UCLASS(Abstract)
class RUNFORLIFE_API ANPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:

	/** Speed for spinning */
	UPROPERTY(EditAnywhere, Category = CharacterCondition)
	float SpinSpeed;
	
	/** Component which senses pawns in sight and noise nearby */
	UPROPERTY(EditAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;
	
	/** Called when seeing a pawn */
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn) PURE_VIRTUAL( , );

	/** Called when hearing noise */
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume) PURE_VIRTUAL( , );
	
public:

	/** Behavior tree component */
	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;
	
	/** Sets default values for this character's properties */
	ANPCCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Returns spin speed */
	FORCEINLINE float GetSpinSpeed() const { return SpinSpeed; }
};
