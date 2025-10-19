// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyDinoValdoAnimation.h"
#include "Monster/MyDinoValdo.h"

void UMyDinoValdoAnimation::AnimNotify_M_StartChase()
{
	AMyDinoValdo* DinoValdo = GetDinovaldo();

	DinoValdo->SetMonsterState(EMonsterState::Chase);

	UE_LOG(LogTemp, Display, TEXT("Testing ChaseAnim Working?"));
}

AMyDinoValdo* UMyDinoValdoAnimation::GetDinovaldo() const
{
	return Cast<AMyDinoValdo>(TryGetPawnOwner());
}
