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

protected:

private:
	class AMyDinoValdo* GetDinovaldo() const;

};
