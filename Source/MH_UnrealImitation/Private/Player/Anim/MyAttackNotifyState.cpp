// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/MyAttackNotifyState.h"
#include "MyPlayerHunter.h"
void UMyAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	UWorld* world = MeshComp->GetWorld();

	if (world == nullptr || world->IsGameWorld() == false)
	{
		return;
	}

	AMyPlayerHunter* PlayerHunter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerHunter != nullptr)
	{
		PlayerHunter->bIsCanMove = false;
	}
}

void UMyAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	UWorld* world = MeshComp->GetWorld();

	if (world == nullptr || world->IsGameWorld() == false)
	{
		return;
	}

	AMyPlayerHunter* PlayerHunter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerHunter != nullptr)
	{
		//PlayerHunter->SetYawRotVector(FVector(0.0f, 0.0f, 0.0f));
		PlayerHunter->bIsCanMove = true;
	}
}
