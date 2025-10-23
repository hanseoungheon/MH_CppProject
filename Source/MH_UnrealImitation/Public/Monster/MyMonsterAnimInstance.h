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

	// �ִϸ��̼� ������Ʈ�� �� ������ ���� ����Ǵ� �Լ�.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState StateAnim = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState PrevStateAnim = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class AMyMonster* Monster = nullptr;
};
