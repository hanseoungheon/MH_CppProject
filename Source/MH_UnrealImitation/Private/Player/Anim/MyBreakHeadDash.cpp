// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/MyBreakHeadDash.h"
#include "MyPlayerHunter.h"

void UMyBreakHeadDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
			BreakHeadTimeLine->PlayFromStart();
	}


}
