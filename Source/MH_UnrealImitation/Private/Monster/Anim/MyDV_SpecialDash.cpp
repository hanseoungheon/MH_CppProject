// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Anim/MyDV_SpecialDash.h"
#include "Monster/MyDinoValdo.h"
void UMyDV_SpecialDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	AMyDinoValdo* DinoValdo = Cast<AMyDinoValdo>(MeshComp->GetOwner());

	if (DinoValdo != nullptr)
	{
		DinoValdo
			->SpecialDashTimeline->PlayFromStart();
	}
}
