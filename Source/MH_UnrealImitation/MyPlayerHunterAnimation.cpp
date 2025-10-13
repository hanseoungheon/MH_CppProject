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
		//���� �̴´�.
		//�׷��ٸ� �� �������� ������ �ִ°��� �Ⱥ��̰� ���� ���̰�.

		AMyPlayerHunter* PlayerCharacter = GetHunter();
		AMyLongSword* LS = PlayerCharacter->LongSword;
		AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


		//���� ������ �Ű��ִ°� ����
		PlayerCharacter->bIsHanging = false;
		//�׸��� ����ִ°� ���̰�.
		LS->SetVisibleWeapon();
		//�׸��� �Ŵ°� �Ⱥ��̰�.
		DummyLS->SetVisibleDummy();
		DummyLS->SetVisibleDummy();
	}
}

void UMyPlayerHunterAnimation::AnimNotify_LS_DrawEnd()
{
	//����̱� ����.
	IsDrawingWeapon = false;
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->SetState(ECharacterState::Battle);

}

AMyPlayerHunter* UMyPlayerHunterAnimation::GetHunter() const
{
	return Cast<AMyPlayerHunter>(TryGetPawnOwner());
}
