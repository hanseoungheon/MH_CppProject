// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyDinoValdo.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AMyDinoValdo::AMyDinoValdo()
{
	WalkSpeed = 200.0f;
	RunSpeed = 600.0f;

	SpecialDashTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpecialDashTimeline"));

	//본소켓에 붙히는 과정.
	//우선 본 이름 정리.
	static const FName HeadBoneName(TEXT("bone_004")); //머리 본.
	static const FName NeckBoneName(TEXT("bone_100")); //목 본.
	static const FName BodyBoneName(TEXT("bone_140")); //몸통 본.

	static const FName LeftLegBoneName(TEXT("bone_014")); //왼쪽 다리 본.
	static const FName LeftFootBoneName(TEXT("bone_080")); //왼쪽 발 본
	static const FName RightLegBoneName(TEXT("bone_018")); // 오른쪽 다리 본
	static const FName RightFootBoneName(TEXT("bone_090")); // 오른쪽 발 본.

	static const FName Tail01BoneName(TEXT("bone_142")); //꼬리 본들.
	static const FName Tail02BoneName(TEXT("bone_144"));
	static const FName Tail03BoneName(TEXT("bone_145"));
	static const FName Tail04BoneName(TEXT("bone_147"));

	//히트박스들 생성
	//--------------------------------------------
	//먼저 히트박스(디노발드가 공격받는 히트박스)
	HitBox_Head //머리
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Head"));

	HitBox_Chest //가슴
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Chest"));

	HitBox_Body //몸통
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Body"));

	HitBox_Leg_Left //왼쪽 다리.
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Leg_L"));
	HitBox_Foot_Left
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Foot_L"));

	HitBox_Leg_Right //오른쪽 다리.
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Leg_R"));
	HitBox_Foot_Right
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Foot_R"));

	HitBox_Tail01 //꼬리
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail01"));
	HitBox_Tail02
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail02"));
	HitBox_Tail03
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail03"));
	HitBox_Tail04
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail04"));
	//--------------------------------------------------------------------
	// 
	//그다음 어택콜리전(디노발드가 공격하는 콜리전 생성)
	AttackCollision_Mouse //입(머리)
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Mouse"));

	AttackCollision_Foot_Left //왼쪽 다리.
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Foot_L"));
	AttackCollision_Foot_Right //오른쪽 다리.
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Foot_R"));

	AttackCollision_Tail01 //꼬리들
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail01"));
	AttackCollision_Tail02 
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail02"));
	AttackCollision_Tail03
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail03"));
	AttackCollision_Tail04
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail04"));


	//이제 콜리전 설정.
	//우선 크기 설정(데미지를 받는 히트박스를 더 크게 250으로/데미지를 주는 어택박스는 200으로)
	HitBoxRadius = 250.0f;
	AttackCollisionRadius = 200.0f;

	//1. 우선 히트박스들을 먼저 Mesh에 붙힌다.
	HitBox_Head->SetupAttachment(GetMesh(),HeadBoneName);
	HitBox_Chest->SetupAttachment(GetMesh(),NeckBoneName);
	HitBox_Body->SetupAttachment(GetMesh(),BodyBoneName);

	HitBox_Leg_Left->SetupAttachment(GetMesh(),LeftLegBoneName);
	HitBox_Foot_Left->SetupAttachment(GetMesh(),LeftFootBoneName);
	HitBox_Leg_Right->SetupAttachment(GetMesh(),RightLegBoneName);
	HitBox_Foot_Right->SetupAttachment(GetMesh(),RightFootBoneName);
	
	HitBox_Tail01->SetupAttachment(GetMesh(),Tail01BoneName);
	HitBox_Tail02->SetupAttachment(GetMesh(),Tail02BoneName);
	HitBox_Tail03->SetupAttachment(GetMesh(),Tail03BoneName);
	HitBox_Tail04->SetupAttachment(GetMesh(),Tail04BoneName);

	//2. 그리고 히트박스들의 크기를 설정한다.
	HitBox_Head->SetSphereRadius(HitBoxRadius);
	HitBox_Chest->SetSphereRadius(HitBoxRadius);
	HitBox_Body->SetSphereRadius(HitBoxRadius);

	HitBox_Leg_Left->SetSphereRadius(HitBoxRadius - 100);
	HitBox_Foot_Left->SetSphereRadius(HitBoxRadius - 100);
	HitBox_Leg_Right->SetSphereRadius(HitBoxRadius- 100);
	HitBox_Foot_Right->SetSphereRadius(HitBoxRadius - 100);

	HitBox_Tail01->SetSphereRadius(HitBoxRadius);
	HitBox_Tail02->SetSphereRadius(HitBoxRadius);
	HitBox_Tail03->SetSphereRadius(HitBoxRadius);
	HitBox_Tail04->SetSphereRadius(HitBoxRadius);

	//3. 그리고 오버랩 이벤트를 할수 있게 미리 키기.
	HitBox_Head->SetGenerateOverlapEvents(true);
	HitBox_Chest->SetGenerateOverlapEvents(true);
	HitBox_Body->SetGenerateOverlapEvents(true);
	HitBox_Leg_Left->SetGenerateOverlapEvents(true);
	HitBox_Foot_Left->SetGenerateOverlapEvents(true);
	HitBox_Leg_Right->SetGenerateOverlapEvents(true);
	HitBox_Foot_Right->SetGenerateOverlapEvents(true);
	HitBox_Tail01->SetGenerateOverlapEvents(true);
	HitBox_Tail02->SetGenerateOverlapEvents(true);
	HitBox_Tail03->SetGenerateOverlapEvents(true);
	HitBox_Tail04->SetGenerateOverlapEvents(true);




	//여기서 히트박스 콜리전 설정은 끝.
	// 
	// 
	//4.그 다음 공격콜리전들을 메시에 붙힌다.
	AttackCollision_Mouse->SetupAttachment(GetMesh(),HeadBoneName);
	AttackCollision_Foot_Left->SetupAttachment(GetMesh(),LeftFootBoneName);
	AttackCollision_Foot_Right->SetupAttachment(GetMesh(),RightFootBoneName);

	AttackCollision_Tail01->SetupAttachment(GetMesh(),Tail01BoneName);
	AttackCollision_Tail02->SetupAttachment(GetMesh(),Tail02BoneName);
	AttackCollision_Tail03->SetupAttachment(GetMesh(),Tail03BoneName);
	AttackCollision_Tail04->SetupAttachment(GetMesh(),Tail04BoneName);


	//5. 그다음 공격 콜리전의 크기를 설정한다.
	AttackCollision_Mouse->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Foot_Left->SetSphereRadius(AttackCollisionRadius - 100);
	AttackCollision_Foot_Right->SetSphereRadius(AttackCollisionRadius - 100);

	AttackCollision_Tail01->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail02->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail03->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail04->SetSphereRadius(AttackCollisionRadius);

	//6. 그다음 공격콜리전들의 오버랩이벤트 반응 여부를 킨다.
	AttackCollision_Mouse->SetGenerateOverlapEvents(true);
	AttackCollision_Foot_Left->SetGenerateOverlapEvents(true);
	AttackCollision_Foot_Right->SetGenerateOverlapEvents(true);

	AttackCollision_Tail01->SetGenerateOverlapEvents(true);
	AttackCollision_Tail02->SetGenerateOverlapEvents(true);
	AttackCollision_Tail03->SetGenerateOverlapEvents(true);
	AttackCollision_Tail04->SetGenerateOverlapEvents(true);
}

void AMyDinoValdo::MonsterDead()
{
	Super::MonsterDead();

	//히트박스 콜리전 전부 끄기.
	HitBox_Head->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Chest->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Leg_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Foot_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Leg_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Foot_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::OnTailAttackBegin() //꼬리어택공격
{
	//꼬리 어택시
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnTailAttackEnd() //꼬리어택종료
{
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::OnSpecialAttackBegin() // 특수공격 시작(대회전베기 등등) 
{
	//잠시 캡슐 컴포넌트 오버랩되게.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//꼬리로도 떄리고
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//다리로도 떄린다.
	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnSpecialAttackEnd() //특수 공격 종료.
{
	//캡슐컴포넌트 다시 충돌시작.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//꼬리로도 떄리는거 종료
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//다리로도 떄리는거 종료
	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::OnMouseAttackBegin() //물기 공격 시작.
{
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnMouseAttackEnd() //물기 공격 종료.
{
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::BeginPlay()
{
	Super::BeginPlay();

	//타임라인.
	if (SpecialDashTimeline != nullptr)
	{
		FOnTimelineFloat SpecialDashInterpFunction;
		FOnTimelineEvent SpecialDashFinishedFunction;

		SpecialDashInterpFunction.BindUFunction(this, FName("DashToSpeicalDash"));
		SpecialDashTimeline->AddInterpFloat(SpecialDashCurve, SpecialDashInterpFunction);

		SpecialDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		SpecialDashTimeline->SetTimelineFinishedFunc(SpecialDashFinishedFunction);

		SpecialDashTimeline->SetLooping(false);
		SpecialDashTimeline->SetPlayRate(1.0f);
	}
}

void AMyDinoValdo::Angry()
{
	Super::Angry();
	//캡슐컴포넌트 다시 오버랩.
	if(GetCapsuleComponent()->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//즉시 어택콜리전 종료.
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//그 후 분노상태로 전환.
	bAngry = true;
}

void AMyDinoValdo::DashToSpeicalDash(float TimeLineValue)
{
	float DashPower = 2000.0f;
	//UE_LOG(LogTemp, Display, TEXT("DINOVALDO SPD TEST"));
	DashToPlayerOfTimeLine(TimeLineValue, DashPower);
}


