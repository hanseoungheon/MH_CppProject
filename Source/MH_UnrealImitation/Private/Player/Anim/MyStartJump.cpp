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

		FVector FowardVector = PlayerHunter->GetActorForwardVector() * 10.0f; //�÷��̾ �ٶ󺸴� �������� Impulse���ؼ� �ùٸ��� ���ư��� ��.
		float JumpPower = 1500.0f; //���� ����.

		CharacterMovement->AddImpulse(FVector(0.0f, FowardVector.Y, JumpPower), true);
	}
}
