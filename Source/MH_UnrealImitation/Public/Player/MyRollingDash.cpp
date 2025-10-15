// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyRollingDash.h"
#include "MyPlayerHunter.h"

void UMyRollingDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	PlayerCharacter->RollingMovemnt();
}
