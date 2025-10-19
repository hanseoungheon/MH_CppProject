// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyMonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMyMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr)
	{
		return;
	}

	if (BBAsset != nullptr)
	{
		UseBlackboard(BBAsset, BBComponent);
	}
	else if (BTAsset && BTAsset->BlackboardAsset)
	{
		// BB를 따로 안 넣었다면, BT에 붙은 BB를 사용
		UseBlackboard(BTAsset->BlackboardAsset, BBComponent);
	}

	if (BBComponent == nullptr)
	{
		return;
	}

	BBComponent->SetValueAsFloat(PatrolWaitTimeKey, PatrolWaitTime);
	BBComponent->SetValueAsVector(OriginalLocationKey, InPawn->GetActorLocation());

	if (BTAsset != nullptr)
	{
		const bool IsCanBBWork = RunBehaviorTree(BTAsset);

		if (IsCanBBWork == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree failed"));
			return;
		}
	}

}
