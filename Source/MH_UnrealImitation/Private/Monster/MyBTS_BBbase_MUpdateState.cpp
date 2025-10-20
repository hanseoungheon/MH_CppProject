// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyBTS_BBbase_MUpdateState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UMyBTS_BBbase_MUpdateState::UMyBTS_BBbase_MUpdateState()
{
	bNotifyTick = true;
	Interval = 0.25f;
	RandomDeviation = 0.05f;

	AttackRange = 500.0f;

	//TargetPlayerKey.AddObjectFilter(this,
	//	GET_MEMBER_NAME_CHECKED(UMyBTS_BBbase_MonsterAttack, TargetPlayerKey),
	//	AActor::StaticClass());
	//DistanceKey.AddFloatFilter(this,
	//	GET_MEMBER_NAME_CHECKED(UMyBTS_BBbase_MonsterAttack, DistanceKey));
	//InRangeKey.AddBoolFilter(this,
	//	GET_MEMBER_NAME_CHECKED(UMyBTS_BBbase_MonsterAttack, InRangeKey));
	//SightKey.AddBoolFilter(this,
	//	GET_MEMBER_NAME_CHECKED(UMyBTS_BBbase_MonsterAttack, SightKey));
}

void UMyBTS_BBbase_MUpdateState::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	TargetPlayerKey.ResolveSelectedKey(*GetBlackboardAsset());
	DistanceKey.ResolveSelectedKey(*GetBlackboardAsset());
	InRangeKey.ResolveSelectedKey(*GetBlackboardAsset());
	SightKey.ResolveSelectedKey(*GetBlackboardAsset());
}


void UMyBTS_BBbase_MUpdateState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AAIController* AICon = OwnerComp.GetAIOwner();
	
	if (AICon == nullptr)
	{
		return;
	}

	APawn* Pawn = AICon->GetPawn(); //���� �����ϴ� ������ �� ��������.

	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetPlayerKey.SelectedKeyName)); //Ÿ���� �� ���� ��������.

	if (Pawn == nullptr || TargetActor == nullptr) //����ó��.
	{
		BB->SetValueAsFloat(DistanceKey.SelectedKeyName, -1.f);
		BB->SetValueAsBool(InRangeKey.SelectedKeyName, false);
		BB->SetValueAsBool(SightKey.SelectedKeyName, false);
		return;
	}

	PawnLocation = Pawn->GetActorLocation();
	TargetLoctation = TargetActor->GetActorLocation();

	Distance = FVector::Dist2D(PawnLocation, TargetLoctation); //���Ϳ� ���� ���̰��� �Ÿ� ���ϱ�.

	BB->SetValueAsFloat(DistanceKey.SelectedKeyName,Distance);

	//���� üũ
	const FVector MonsterFwd = Pawn->GetActorForwardVector();
	const FVector MonsterDir = (TargetLoctation - PawnLocation).GetSafeNormal2D();
	const float AngleDeg = FMath::RadiansToDegrees(acosf(FVector::DotProduct(MonsterFwd, MonsterDir)));
	bAngleOk = AngleDeg <= HalfAngleDeg;

	const bool bIsInRange = (Distance <= AttackRange) && bAngleOk;
	BB->SetValueAsBool(InRangeKey.SelectedKeyName, bIsInRange);

	//�þ� üũ
	FHitResult Hit;
	FCollisionQueryParams Params(NAME_None, false, Pawn);
	bLineOfSight = Pawn->GetWorld()->LineTraceSingleByChannel(
		Hit, PawnLocation + FVector(0, 0, 50), TargetLoctation + FVector(0, 0, 50), ECC_Visibility, Params);

	BB->SetValueAsBool(SightKey.SelectedKeyName, !bLineOfSight);
	
}
