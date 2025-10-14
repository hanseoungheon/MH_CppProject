// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterState.h"
#include "MyPlayerHunterAnimation.generated.h"

/**
 * 
 */

UCLASS()
class MH_UNREALIMITATION_API UMyPlayerHunterAnimation : public UAnimInstance
{
	GENERATED_BODY()

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
	void AninNotify_LS_AttckEnd();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState StateAnim = ECharacterState::Peace;
private:
	class AMyPlayerHunter* GetHunter() const;

	
};
