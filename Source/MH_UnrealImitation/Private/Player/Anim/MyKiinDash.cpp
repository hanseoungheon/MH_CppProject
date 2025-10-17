// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/MyKiinDash.h"
#include "MyPlayerHunter.h"

void UMyKiinDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	UWorld* world = MeshComp->GetWorld();

	if (world == nullptr || world->IsGameWorld() == false)
	{
		return;
	}

	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->
			KiinDashTimeLine->PlayFromStart();
		UE_LOG(LogTemp, Display, TEXT("돌진이 되나 디버깅용 텍스트입니다."));
	}
}
