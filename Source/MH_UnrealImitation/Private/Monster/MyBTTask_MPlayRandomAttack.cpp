// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyBTTask_MPlayRandomAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Monster/MyMoster.h"
#include "Animation/AnimMontage.h"

UMyBTTask_MPlayRandomAttack::UMyBTTask_MPlayRandomAttack()
{
	bPreventRepeat = true;
	bStopMovementDuringAttack = true;
	PlayRate = 1.0f;

	bNotifyTick = false;
}

EBTNodeResult::Type UMyBTTask_MPlayRandomAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;

	AAIController* AICon = OwnerComp.GetAIOwner(); //AI 컨트롤러 가져오기.

	if (AICon == nullptr) //만약 가져오지 못할시 실패처리.
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Character = Cast<ACharacter>(AICon->GetPawn()); //캐릭터 가져오기.

	if (Character == nullptr)//만약 가져오지 못할시 실패처리.
	{
		return EBTNodeResult::Failed;
	}

	AMyMonster* Monster = Cast<AMyMonster>(Character);

	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const TArray<UAnimMontage*>& MonsterAttackMontages = Monster->AttackMontages;

	if (MonsterAttackMontages.Num() == 0) //몽타주 벡터가 없을시 실패처리.
	{
		return EBTNodeResult::Failed;
	}

	if (bStopMovementDuringAttack)
	{
		AICon->StopMovement();
	}

	int32 MaxIndex = MonsterAttackMontages.Num() - 1;
	int32 ChoseIndex = FMath::RandRange(0, MaxIndex);

	if (bPreventRepeat == true && MonsterAttackMontages.Num() > 1 && ChoseIndex == LastIndex)
	{
		ChoseIndex = (ChoseIndex + 1) % MonsterAttackMontages.Num();
	}

	LastIndex = ChoseIndex;

	UAnimMontage* ChosenMontage = MonsterAttackMontages.IsValidIndex(ChoseIndex)  //만약 인덱스가 정상적인 범위이면 해당 인덱스에 위치한 몽타주를 가져옴.
		? MonsterAttackMontages[ChoseIndex] : nullptr;

	if (ChosenMontage == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInst = Character->GetMesh() 
		? Character->GetMesh()->GetAnimInstance() : nullptr; //만약 메시가 존재할때만 메시에 존재하는 애님 인스턴스를 가져옴.

	if (AnimInst == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	BoundAnimInstance = AnimInst;
	PlayingMontage = ChosenMontage;

	// IMPORTANT: AddDynamic requires that OnMontageEnded is a dynamic multicast (it is in UE)
	AnimInst->OnMontageEnded.AddDynamic(this, &UMyBTTask_MPlayRandomAttack::OnMontageEnded);

	// Play
	AnimInst->Montage_Play(ChosenMontage, 1.0f);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UMyBTTask_MPlayRandomAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BoundAnimInstance != nullptr)
	{
		if (PlayingMontage != nullptr && BoundAnimInstance->Montage_IsPlaying(PlayingMontage) == true)
		{
			BoundAnimInstance->Montage_Stop(0.15f,PlayingMontage);
		}

		BoundAnimInstance->OnMontageEnded.RemoveDynamic(this, &UMyBTTask_MPlayRandomAttack::OnMontageEnded);
	}

	BoundAnimInstance = nullptr;
	PlayingMontage = nullptr;

	CachedOwnerComp = nullptr;

	return EBTNodeResult::Aborted;
}

void UMyBTTask_MPlayRandomAttack::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (CachedOwnerComp == nullptr)
	{
		return;
	}

	if (BoundAnimInstance)
	{
		BoundAnimInstance->OnMontageEnded.RemoveDynamic(this, &UMyBTTask_MPlayRandomAttack::OnMontageEnded);
	}

	FinishLatentTask(*CachedOwnerComp, bInterrupted ? EBTNodeResult::Aborted : EBTNodeResult::Succeeded);

	BoundAnimInstance = nullptr;
	PlayingMontage = nullptr;
	CachedOwnerComp = nullptr;
}
