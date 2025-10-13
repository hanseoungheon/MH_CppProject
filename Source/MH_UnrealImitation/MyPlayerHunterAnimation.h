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
	UFUNCTION()
	void AnimNotify_LS_Draw();
	
	UFUNCTION()
	void AnimNotify_LS_DrawEnd();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState StateAnim = ECharacterState::Peace;
private:
	class AMyPlayerHunter* GetHunter() const;

	bool IsDrawingWeapon = false;

	
};
