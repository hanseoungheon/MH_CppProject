// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/MyRollingDash.h"
#include "MyPlayerHunter.h"

void UMyRollingDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
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

	if (PlayerCharacter!= nullptr && PlayerCharacter->RollingTimeLine != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("이거 동작하는지 테스트"));
		PlayerCharacter->
			RollingTimeLine->PlayFromStart();
	}

}
