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
		//SetPrevState를 통해서 현재 순간의 State를 임시로 PrevStateAnim에 저장 후 Stagte를 변경.
		PlayerCharacter->SetPrevState();
		PrevState_Notify = PlayerCharacter->GetPrevState();

		AController* CharacterController = PlayerCharacter->GetController();

		if (CharacterController != nullptr)
		{
			//상태를 Roll로 변경.
			PlayerCharacter->SetState(ECharacterState::Roll);

			//구르기 시작시 입력부분 입력만 막음.
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

	//Mesh컴포넌트의 주인인 액터에 접근 후에 MyPlayerHunter로 캐스팅 후 성공 시 형변환.
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(MeshComp->GetOwner());

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->bIsRolling = false;

		AController* CharacterController = PlayerCharacter->GetController();

		if (CharacterController != nullptr)
		{
			PlayerCharacter->SetState(PrevState_Notify);
			//끝나면 캐릭터의 입력잠금을 다시끔
			CharacterController->SetIgnoreMoveInput(false);
		}
	}


}
