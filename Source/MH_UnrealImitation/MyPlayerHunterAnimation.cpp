// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunterAnimation.h"
#include "MyPlayerHunter.h"
#include "MyLongSword.h"
#include "MyDummyWeapon.h"

void UMyPlayerHunterAnimation::AnimNotify_LS_Draw()
{
	if (IsDrawingWeapon == false)
	{
		UE_LOG(LogTemp, Display, TEXT("IsWorkingNow"));
		IsDrawingWeapon = true;
		//검을 뽑는다.
		//그렇다면 이 시점에서 검집에 있는검은 안보이게 검은 보이게.

		AMyPlayerHunter* PlayerCharacter = GetHunter();
		AMyLongSword* LS = PlayerCharacter->LongSword;
		AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


		//검을 뽑으니 매고있는검 해제
		PlayerCharacter->bIsHanging = false;
		//그리고 들고있는검 보이게.
		LS->SetVisibleWeapon();
		//그리고 매는검 안보이게.
		DummyLS->SetVisibleDummy();
		DummyLS->SetVisibleDummy();
	}
}

void UMyPlayerHunterAnimation::AnimNotify_LS_DrawEnd()
{
	//무기뽑기 종료.
	IsDrawingWeapon = false;
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->SetState(ECharacterState::Battle);

}

AMyPlayerHunter* UMyPlayerHunterAnimation::GetHunter() const
{
	return Cast<AMyPlayerHunter>(TryGetPawnOwner());
}
