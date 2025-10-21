// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyMonsterState.h"
#include "MyDinoValdoAnimation.generated.h"

/**
 *
 */
UCLASS()
class MH_UNREALIMITATION_API UMyDinoValdoAnimation : public UAnimInstance
{
	GENERATED_BODY()


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





protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState StateAnim = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState PrevStateAnim = EMonsterState::Peace;

private:
	class AMyDinoValdo* GetDinovaldo() const;

};
