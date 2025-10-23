// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimInstance.h"
#include "MyMonsterState.h"
#include "MyMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API UMyMonsterAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()

public:
	UMyMonsterAnimInstance();
protected:
	virtual void NativeInitializeAnimation() override;

	// 애니메이션 업데이트할 때 프레임 마다 실행되는 함수.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState StateAnim = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState PrevStateAnim = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class AMyMonster* Monster = nullptr;
};
