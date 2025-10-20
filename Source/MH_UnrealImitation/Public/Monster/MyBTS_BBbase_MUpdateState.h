// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTS_BBbase_MUpdateState.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API UMyBTS_BBbase_MUpdateState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTS_BBbase_MUpdateState();

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


public:
	UPROPERTY(EditAnywhere, Category = "BB")
	FBlackboardKeySelector TargetPlayerKey;

	UPROPERTY(EditAnywhere, Category = "BB")
	FBlackboardKeySelector DistanceKey;

	UPROPERTY(EditAnywhere, Category = "BB")
	FBlackboardKeySelector InRangeKey;

	UPROPERTY(EditAnywhere, Category = "BB")
	FBlackboardKeySelector SightKey;
	

	UPROPERTY(EditAnywhere, Category = "BB")
	float AttackRange;
	UPROPERTY(EditAnywhere, Category = "BB")
	float Distance;
	UPROPERTY(EditAnywhere, Category = "BB")
	float HalfAngleDeg;

	UPROPERTY(EditAnywhere, Category = "BB")
	FVector PawnLocation;
	UPROPERTY(EditAnywhere, Category = "BB")
	FVector TargetLoctation;

	UPROPERTY(EditAnywhere, Category = "BB")
	bool bLineOfSight = false;
	UPROPERTY(EditAnywhere, Category = "BB")
	bool bAngleOk = false;

	UPROPERTY(EditAnywhere, Category = "BB")
	FName NewVar = NAME_None;


};
