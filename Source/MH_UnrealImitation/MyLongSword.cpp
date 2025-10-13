// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLongSword.h"
#include "MyPlayerHunter.h"

void AMyLongSword::BeginPlay()
{
	Super::BeginPlay();

	//태도만의 기본 데미지 설정하기.
	//어..음 물론 다른 데미지도 설정해야함 그건 차차 하기
	baseDamage = longSwordBaseDamage;
}

void AMyLongSword::IsOverlapToSphere(AActor* OtherActor)
{
	Super::IsOverlapToSphere(OtherActor);

	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		//여기서 겹치면 플레이어를 주인으로 설정
		PlayerCharacter->IsInteract_PickUpWeapon(true, this);
	}

}

void AMyLongSword::IsEndOverlapToSphere(AActor* OtherActor)
{
	Super::IsEndOverlapToSphere(OtherActor);

	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		//여기서 벗어나면 주인 해제.
		PlayerCharacter->IsInteract_PickUpWeapon(false, this);
	}

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


