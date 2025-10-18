// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/MyStartJump.h"
#include "MyPlayerHunter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyStartJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
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
		UCharacterMovementComponent* CharacterMovement = PlayerHunter->GetCharacterMovement();

		FVector FowardVector = PlayerHunter->GetActorForwardVector() * 10.0f; //플레이어가 바라보는 방향으로 Impulse를해서 올바르게 날아가게 함.
		float JumpPower = 1500.0f; //점프 높이.

		CharacterMovement->AddImpulse(FVector(0.0f, FowardVector.Y, JumpPower), true);
	}
}
