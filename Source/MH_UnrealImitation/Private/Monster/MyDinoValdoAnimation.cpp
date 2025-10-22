// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyDinoValdoAnimation.h"
#include "Monster/MyDinoValdo.h"
#include "GameFramework\Character.h"
#include "GameFramework\CharacterMovementComponent.h"

UMyDinoValdoAnimation::UMyDinoValdoAnimation()
{
}

void UMyDinoValdoAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	//나중에 상속구조 다시 만들어보기.
}

void UMyDinoValdoAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//나중에 상속구조 다시 만들어보기.
}

void UMyDinoValdoAnimation::AnimNotify_M_StartChase()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	DinoValdo->SetMonsterState(EMonsterState::Chase);

	UE_LOG(LogTemp, Display, TEXT("Testing ChaseAnim Working?"));
}

void UMyDinoValdoAnimation::AnimNotify_DV_BiteStart()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if(DinoValdo != nullptr)
		DinoValdo->OnMouseAttackBegin();
}

void UMyDinoValdoAnimation::AnimNotify_DV_BiteEnd()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if (DinoValdo != nullptr)
		DinoValdo->OnMouseAttackEnd();
}

void UMyDinoValdoAnimation::AnimNotify_DV_TailAttack_Start()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if (DinoValdo != nullptr)
		DinoValdo->OnTailAttackBegin();
}

void UMyDinoValdoAnimation::AnimNotify_DV_TailAttack_End()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if (DinoValdo != nullptr)
		DinoValdo->OnTailAttackEnd();
}

void UMyDinoValdoAnimation::AnimNotify_DV_SpecialAttack_Start()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if (DinoValdo != nullptr)
		DinoValdo->OnSpecialAttackBegin();
}

void UMyDinoValdoAnimation::AnimNotify_DV_SpecialAttack_End()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	if (DinoValdo != nullptr)
		DinoValdo->OnSpecialAttackEnd();
}

AMyDinoValdo* UMyDinoValdoAnimation::GetDinovaldo() const
{
	return Cast<AMyDinoValdo>(TryGetPawnOwner());
}
