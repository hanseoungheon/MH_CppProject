// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MyRollingDash.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API UMyRollingDash : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
private:
};
