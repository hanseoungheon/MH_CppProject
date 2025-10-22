// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimInstance.h"
#include "MyCharacterState.h"
#include "MyPlayerHunterAnimation.generated.h"

/**
 * 
 */

UCLASS()
class MH_UNREALIMITATION_API UMyPlayerHunterAnimation : public UMyAnimInstance
{
	GENERATED_BODY()


public:
	UMyPlayerHunterAnimation();
protected:
	// 애니메이션 초기화할 때 실행되는 함수.
	virtual void NativeInitializeAnimation() override;

	// 애니메이션 업데이트할 때 프레임 마다 실행되는 함수.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Draw")
	void AnimNotify_LS_Draw();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Draw")
	void AnimNotify_LS_DrawEnd();

	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Sheath")
	void AnimNotify_LS_Sheath();

	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Sheath")
	void AnimNotify_LS_SheathEnd();

	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Attack")
	void AnimNotify_LS_AttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Weapom/LongSword/Attack")
	void AnimNotify_LS_BreakHeadHit();

	UFUNCTION(BlueprintCallable, Category = "Weapon/LongSword/Attack")
	void AnimNotify_LS_IaiReady();

	UFUNCTION(BlueprintCallable, Category = "Weapon/Attack")
	void AnimNotify_Wp_AttackBegin();

	UFUNCTION(BlueprintCallable, Category = "Weapon/Attack")
	void AnimNotify_Wp_AttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_RollingStart();
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_RollingEnd();

	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_LS_GanpaStart();
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_LS_GanpaEnd();

	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_LS_IaiStart();
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AnimNotify_LS_IaiEnd();



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState StateAnim = ECharacterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState PrevStateAnim = ECharacterState::Peace;

	//뛰고있는지 판단하는 함수.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool bIsRunAnim = false;
private:
	class AMyPlayerHunter* GetHunter() const;

	
};
