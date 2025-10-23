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

	AAIController* AICon = OwnerComp.GetAIOwner(); //AI ��Ʈ�ѷ� ��������.

	if (AICon == nullptr) //���� �������� ���ҽ� ����ó��.
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Character = Cast<ACharacter>(AICon->GetPawn()); //ĳ���� ��������.

	if (Character == nullptr)//���� �������� ���ҽ� ����ó��.
	{
		return EBTNodeResult::Failed;
	}

	AMyMonster* Monster = Cast<AMyMonster>(Character);

	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const TArray<UAnimMontage*>& MonsterAttackMontages = Monster->AttackMontages;

	if (MonsterAttackMontages.Num() == 0) //��Ÿ�� ���Ͱ� ������ ����ó��.
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

	UAnimMontage* ChosenMontage = MonsterAttackMontages.IsValidIndex(ChoseIndex)  //���� �ε����� �������� �����̸� �ش� �ε����� ��ġ�� ��Ÿ�ָ� ������.
		? MonsterAttackMontages[ChoseIndex] : nullptr;

	if (ChosenMontage == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInst = Character->GetMesh() 
		? Character->GetMesh()->GetAnimInstance() : nullptr; //���� �޽ð� �����Ҷ��� �޽ÿ� �����ϴ� �ִ� �ν��Ͻ��� ������.

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
