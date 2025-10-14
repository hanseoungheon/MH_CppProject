// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunterAnimation.h"
#include "MyPlayerHunter.h"
#include "MyLongSword.h"
#include "MyDummyWeapon.h"

void UMyPlayerHunterAnimation::AnimNotify_LS_Draw()
{
		//UE_LOG(LogTemp, Display, TEXT("IsWorkingNow"));
		//검을 뽑는다.
		//그렇다면 이 시점에서 검집에 있는검은 안보이게 검은 보이게.

		AMyPlayerHunter* PlayerCharacter = GetHunter();
		AMyLongSword* LS = PlayerCharacter->LongSword;
		AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


		//검을 뽑았으니 발도상태로 전환.
		PlayerCharacter->SetState(ECharacterState::Battle);

		//그리고 들고있는검 보이게.
		LS->SetVisibleWeapon();
		//그리고 매는검 안보이게.
		DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_DrawEnd()
{
	//무기뽑기 종료.
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->bIsCanAttack = true; //플레이어가 공격 가능한 상태로 전환.
	PlayerCharacter->bIsDrawWeapon = false; //플레이어가 검을 뽑고있는상태를 끔.
}

void UMyPlayerHunterAnimation::AnimNotify_LS_Sheath()
{
	//검을 집어넣는다.
	//그렇다면 이 시점에서 손에 든 검은 보이지 않게.

	AMyPlayerHunter* PlayerCharacter = GetHunter();
	AMyLongSword* LS = PlayerCharacter->LongSword;
	AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


	//검을 넣었으니 비전투상태로 전환.
	PlayerCharacter->SetState(ECharacterState::Peace);

	//그리고 들고있는검 보이게.
	LS->SetVisibleWeapon();
	//그리고 매는검 안보이게.
	DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_SheathEnd()
{
	//납도하기 종료.
	AMyPlayerHunter* PlayerCharacter = GetHunter();


	PlayerCharacter->bIsSheathWepaon = false;
}

void UMyPlayerHunterAnimation::AninNotify_LS_AttckEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	UE_LOG(LogTemp, Display, TEXT("IsThatWorking?"));
	//공격중인 상태 종료.
	PlayerCharacter->bIsAttacking = false;

	//공격 가능한 상태로 전환.
	PlayerCharacter->bIsCanAttack = true;
}

AMyPlayerHunter* UMyPlayerHunterAnimation::GetHunter() const
{
	return Cast<AMyPlayerHunter>(TryGetPawnOwner());
}
