// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLongSword.h"

void AMyLongSword::BeginPlay()
{
	Super::BeginPlay();

	//�µ����� �⺻ ������ �����ϱ�.
	//��..�� ���� �ٸ� �������� �����ؾ��� �װ� ���� �ϱ�
	baseDamage = longSwordBaseDamage;
}
void AMyLongSword::SwitchLongSwordLevel()
{
	switch (KiinLevel)
	{
	case ELongSwordLevel::LSLevel0:
		KiinLevel = ELongSwordLevel::LSLevel1;
		break;

	case ELongSwordLevel::LSLevel1:
		KiinLevel = ELongSwordLevel::LSLevel2;
		break;

	case ELongSwordLevel::LSLevel2:
		KiinLevel = ELongSwordLevel::LSLevel3;
		break;
	}
}


