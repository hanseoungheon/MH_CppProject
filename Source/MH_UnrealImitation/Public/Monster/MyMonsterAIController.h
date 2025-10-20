// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API AMyMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	FORCEINLINE UBlackboardComponent* GetBlackBoardComponent() const
	{
		return BBComponent;
	}

	
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BTAsset = nullptr;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBlackboardData* BBAsset = nullptr;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBlackboardComponent* BBComponent = nullptr;


	UPROPERTY(EditAnywhere, Category = "AI|BlackboardKeys")
	FName PatrolWaitTimeKey = TEXT("PatrolWaitTime");

	UPROPERTY(EditAnywhere, Category = "AI|BlackboardKeys")
	FName OriginalLocationKey = TEXT("OriginalLocation");

	UPROPERTY(EditAnywhere, Category = "AI")
	float PatrolWaitTime = 2.0f;

};
