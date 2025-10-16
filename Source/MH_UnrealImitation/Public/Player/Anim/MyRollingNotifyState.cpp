// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRollingNotifyState.h"
#include "Player/MyPlayerHunter.h"

void UMyRollingNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
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

	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerCharacter != nullptr)
	{
		//SetPrevState�� ���ؼ� ���� ������ State�� �ӽ÷� PrevStateAnim�� ���� �� Stagte�� ����.
		PlayerCharacter->SetPrevState();
		PrevState_Notify = PlayerCharacter->GetPrevState();

		AController* CharacterController = PlayerCharacter->GetController();

		if (CharacterController != nullptr)
		{
			//���¸� Roll�� ����.
			PlayerCharacter->SetState(ECharacterState::Roll);

			//������ ���۽� �Էºκ� �Է¸� ����.
			CharacterController->SetIgnoreMoveInput(true);
		}
	}

}

void UMyRollingNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	//Mesh������Ʈ�� ������ ���Ϳ� ���� �Ŀ� MyPlayerHunter�� ĳ���� �� ���� �� ����ȯ.
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->bIsRolling = false;

		AController* CharacterController = PlayerCharacter->GetController();

		if (CharacterController != nullptr)
		{
			PlayerCharacter->SetState(PrevState_Notify);
			//������ ĳ������ �Է������ �ٽò�
			CharacterController->SetIgnoreMoveInput(false);
		}
	}


}
