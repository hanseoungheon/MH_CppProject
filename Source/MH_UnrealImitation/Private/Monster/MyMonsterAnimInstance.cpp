// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyMonsterAnimInstance.h"
#include "MyMonsterAnimInstance.h"
#include "MyMoster.h"
UMyMonsterAnimInstance::UMyMonsterAnimInstance()
{
}

void UMyMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMyMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Monster = Cast<AMyMonster>(Character);

	if (Monster != nullptr)
	{
		//상태 가져오기.
		PrevStateAnim = Monster->GetMonsterPreState();
		StateAnim = Monster->GetMonsterState();
	}
}
