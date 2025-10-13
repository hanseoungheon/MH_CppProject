// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDummyLSHouse.h"
#include "MyPlayerHunter.h"
#include "MyLongSword.h"

void AMyDummyLSHouse::SetVisibleDummy()
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(GetOwner());

	if (PlayerCharacter != nullptr && PlayerCharacter->bHasWeapon)
	{
		AMyLongSword* PlayerLongSword = Cast<AMyLongSword>(PlayerCharacter->LongSword);

		if (PlayerLongSword != nullptr)
		{
			bool Trigger = PlayerLongSword->bIsIai;
			Trigger ?
				DummyWeaponMesh->SetVisibility(false) : DummyWeaponMesh->SetVisibility(true);
		}
	}
}

void AMyDummyLSHouse::SetVisibleLSHouse()
{
	SetVisibleDummy();
}
