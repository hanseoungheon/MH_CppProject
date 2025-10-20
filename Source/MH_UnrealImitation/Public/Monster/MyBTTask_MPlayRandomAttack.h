// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Animation/AnimInstance.h"
#include "MyBTTask_MPlayRandomAttack.generated.h"

/**
 * 
 */

class UAnimMontage;
class AMyMonster;

UCLASS()
class MH_UNREALIMITATION_API UMyBTTask_MPlayRandomAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMyBTTask_MPlayRandomAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	UPROPERTY(EditAnywhere, Category = "Attack")
	bool bPreventRepeat = true;


	UPROPERTY(EditAnywhere, Category = "Attack")
	bool bStopMovementDuringAttack = true;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float PlayRate;


protected:
	UAnimInstance* BoundAnimInstance = nullptr;

	UBehaviorTreeComponent* CachedOwnerComp = nullptr;

	UAnimMontage* PlayingMontage = nullptr;

	int32 LastIndex = INDEX_NONE;
};
