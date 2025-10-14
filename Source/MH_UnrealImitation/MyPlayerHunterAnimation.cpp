// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunterAnimation.h"
#include "MyPlayerHunter.h"
#include "MyLongSword.h"
#include "MyDummyWeapon.h"

void UMyPlayerHunterAnimation::AnimNotify_LS_Draw()
{
		//UE_LOG(LogTemp, Display, TEXT("IsWorkingNow"));
		//���� �̴´�.
		//�׷��ٸ� �� �������� ������ �ִ°��� �Ⱥ��̰� ���� ���̰�.

		AMyPlayerHunter* PlayerCharacter = GetHunter();
		AMyLongSword* LS = PlayerCharacter->LongSword;
		AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


		//���� �̾����� �ߵ����·� ��ȯ.
		PlayerCharacter->SetState(ECharacterState::Battle);

		//�׸��� ����ִ°� ���̰�.
		LS->SetVisibleWeapon();
		//�׸��� �Ŵ°� �Ⱥ��̰�.
		DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_DrawEnd()
{
	//����̱� ����.
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->bIsCanAttack = true; //�÷��̾ ���� ������ ���·� ��ȯ.
	PlayerCharacter->bIsDrawWeapon = false; //�÷��̾ ���� �̰��ִ»��¸� ��.
}

void UMyPlayerHunterAnimation::AnimNotify_LS_Sheath()
{
	//���� ����ִ´�.
	//�׷��ٸ� �� �������� �տ� �� ���� ������ �ʰ�.

	AMyPlayerHunter* PlayerCharacter = GetHunter();
	AMyLongSword* LS = PlayerCharacter->LongSword;
	AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


	//���� �־����� ���������·� ��ȯ.
	PlayerCharacter->SetState(ECharacterState::Peace);

	//�׸��� ����ִ°� ���̰�.
	LS->SetVisibleWeapon();
	//�׸��� �Ŵ°� �Ⱥ��̰�.
	DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_SheathEnd()
{
	//�����ϱ� ����.
	AMyPlayerHunter* PlayerCharacter = GetHunter();


	PlayerCharacter->bIsSheathWepaon = false;
}

void UMyPlayerHunterAnimation::AninNotify_LS_AttckEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	UE_LOG(LogTemp, Display, TEXT("IsThatWorking?"));
	//�������� ���� ����.
	PlayerCharacter->bIsAttacking = false;

	//���� ������ ���·� ��ȯ.
	PlayerCharacter->bIsCanAttack = true;
}

AMyPlayerHunter* UMyPlayerHunterAnimation::GetHunter() const
{
	return Cast<AMyPlayerHunter>(TryGetPawnOwner());
}
