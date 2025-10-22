// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMonsterAnimInstance.h"
#include "MyDinoValdoAnimation.generated.h"

/**
 *
 */
UCLASS()
class MH_UNREALIMITATION_API UMyDinoValdoAnimation : public UMyMonsterAnimInstance

{
	GENERATED_BODY()


public:
	UMyDinoValdoAnimation();
protected:
	// �ִϸ��̼� �ʱ�ȭ�� �� ����Ǵ� �Լ�.
	virtual void NativeInitializeAnimation() override;

	// �ִϸ��̼� ������Ʈ�� �� ������ ���� ����Ǵ� �Լ�.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Chase")
	void AnimNotify_M_StartChase();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_BiteStart();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_BiteEnd();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_TailAttack_Start();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_TailAttack_End();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_SpecialAttack_Start();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AnimNotify_DV_SpecialAttack_End();

private:
	class AMyDinoValdo* GetDinovaldo() const;

};
