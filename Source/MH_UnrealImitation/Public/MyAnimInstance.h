// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

	// �ִϸ��̼� ������Ʈ�� �� ������ ���� ����Ǵ� �Լ�.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	class ACharacter* Character = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	class UCharacterMovementComponent* CharacterMovement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FVector MyVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshold;



	
};
