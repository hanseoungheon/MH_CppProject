// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunterAnimation.h"
#include "MyPlayerHunter.h"
#include "Weapon/MyLongSword.h"
#include "Weapon/MyDummyWeapon.h"
#include "Animation/AnimMontage.h"

void UMyPlayerHunterAnimation::AnimNotify_LS_Draw()
{
		//UE_LOG(LogTemp, Display, TEXT("IsWorkingNow"));
		//���� �̴´�.
		//�׷��ٸ� �� �������� ������ �ִ°��� �Ⱥ��̰� ���� ���̰�.

		AMyPlayerHunter* PlayerCharacter = GetHunter();
		AMyLongSword* LS = PlayerCharacter->LongSword;
		AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


		//���� �̾����� �ߵ����·� ��ȯ.
		PlayerCharacter->SetState(ECharacterState::Draw);

		//�׸��� ����ִ°� ���̰�.
		LS->SetVisibleWeapon();
		//�׸��� �Ŵ°� �Ⱥ��̰�.
		DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_DrawEnd()
{
	//����̱� ����.
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	//���� �����غ� �Ϸ������ �������·� ����.
	PlayerCharacter->SetState(ECharacterState::Battle);

	PlayerCharacter->bIsDrawWeapon = false; //�÷��̾ ���� �̰��ִ»��¸� ��.
}

void UMyPlayerHunterAnimation::AnimNotify_LS_Sheath()
{
	//���� ����ִ´�.
	//�׷��ٸ� �� �������� �տ� �� ���� ������ �ʰ�.

	AMyPlayerHunter* PlayerCharacter = GetHunter();
	AMyLongSword* LS = PlayerCharacter->LongSword;
	AMyDummyWeapon* DummyLS = PlayerCharacter->DummyLongSword;


	//���� �ִ������� �������·� ��ȯ
	PlayerCharacter->SetState(ECharacterState::Sheath);

	//�׸��� ����ִ°� ���̰�.
	LS->SetVisibleWeapon();
	//�׸��� �Ŵ°� �Ⱥ��̰�.
	DummyLS->SetVisibleDummy();
}

void UMyPlayerHunterAnimation::AnimNotify_LS_SheathEnd()
{
	//�����ϱ� ����.
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	//���� ���������¿� ����
	PlayerCharacter->SetState(ECharacterState::Peace);

	PlayerCharacter->bIsSheathWepaon = false;
}

void UMyPlayerHunterAnimation::AnimNotify_LS_AttackEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	//UE_LOG(LogTemp, Display, TEXT("IsThatWorking?"));
	//�������� ���� ����.
	
	//����ó��. �ߵ��� ����ó��.
	if (PlayerCharacter->GetCharacterState() == ECharacterState::Iai)
	{
		ECharacterState NewState = PlayerCharacter->GetPrevState();
		PlayerCharacter->SetState(NewState);
	}

	PlayerCharacter->bIsAttacking = false;
}

void UMyPlayerHunterAnimation::AnimNotify_LS_BreakHeadHit()
{
	UAnimMontage* BreakHeadMontage = GetHunter()->BreakHead_LS;

	Montage_JumpToSection(TEXT("BeginFly"),BreakHeadMontage);
}

void UMyPlayerHunterAnimation::AnimNotify_LS_IaiReady()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->SetState(ECharacterState::Iai);
}

void UMyPlayerHunterAnimation::AnimNotify_Wp_AttackBegin()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->OnHunterAttackCheckBegin();
}

void UMyPlayerHunterAnimation::AnimNotify_Wp_AttackEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->OnHunterAttackCheckEnd();
}

void UMyPlayerHunterAnimation::AnimNotify_RollingStart()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->Dodge_Roll = true;

}

void UMyPlayerHunterAnimation::AnimNotify_RollingEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	PlayerCharacter->Dodge_Roll = false;
}

void UMyPlayerHunterAnimation::AnimNotify_LS_GanpaStart()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	if (PlayerCharacter->LongSword != nullptr)
	{
		PlayerCharacter->LongSword->Dodge_Ganpa = true;
	}
}

void UMyPlayerHunterAnimation::AnimNotify_LS_GanpaEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	if (PlayerCharacter->LongSword != nullptr)
	{
		PlayerCharacter->LongSword->Dodge_Ganpa = false;
	}
}

void UMyPlayerHunterAnimation::AnimNotify_LS_IaiStart()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	if (PlayerCharacter->LongSword != nullptr)
	{
		PlayerCharacter->LongSword->Dodge_Iai = true;
	}
}

void UMyPlayerHunterAnimation::AnimNotify_LS_IaiEnd()
{
	AMyPlayerHunter* PlayerCharacter = GetHunter();

	if (PlayerCharacter->LongSword != nullptr)
	{
		PlayerCharacter->LongSword->Dodge_Iai = true;
	}
}

FORCEINLINE AMyPlayerHunter* UMyPlayerHunterAnimation::GetHunter() const
{
	return Cast<AMyPlayerHunter>(TryGetPawnOwner());
}
