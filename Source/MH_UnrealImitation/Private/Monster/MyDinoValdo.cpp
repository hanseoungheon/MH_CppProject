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

	//�����Ͽ� ������ ����.
	//�켱 �� �̸� ����.
	static const FName HeadBoneName(TEXT("bone_004")); //�Ӹ� ��.
	static const FName NeckBoneName(TEXT("bone_100")); //�� ��.
	static const FName BodyBoneName(TEXT("bone_140")); //���� ��.

	static const FName LeftLegBoneName(TEXT("bone_014")); //���� �ٸ� ��.
	static const FName LeftFootBoneName(TEXT("bone_080")); //���� �� ��
	static const FName RightLegBoneName(TEXT("bone_018")); // ������ �ٸ� ��
	static const FName RightFootBoneName(TEXT("bone_090")); // ������ �� ��.

	static const FName Tail01BoneName(TEXT("bone_142")); //���� ����.
	static const FName Tail02BoneName(TEXT("bone_144"));
	static const FName Tail03BoneName(TEXT("bone_145"));
	static const FName Tail04BoneName(TEXT("bone_147"));

	//��Ʈ�ڽ��� ����
	//--------------------------------------------
	//���� ��Ʈ�ڽ�(���ߵ尡 ���ݹ޴� ��Ʈ�ڽ�)
	HitBox_Head //�Ӹ�
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Head"));

	HitBox_Chest //����
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Chest"));

	HitBox_Body //����
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Body"));

	HitBox_Leg_Left //���� �ٸ�.
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Leg_L"));
	HitBox_Foot_Left
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Foot_L"));

	HitBox_Leg_Right //������ �ٸ�.
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Leg_R"));
	HitBox_Foot_Right
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Foot_R"));

	HitBox_Tail01 //����
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail01"));
	HitBox_Tail02
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail02"));
	HitBox_Tail03
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail03"));
	HitBox_Tail04
		= CreateDefaultSubobject<USphereComponent>(TEXT("HitBox_Tail04"));
	//--------------------------------------------------------------------
	// 
	//�״��� �����ݸ���(���ߵ尡 �����ϴ� �ݸ��� ����)
	AttackCollision_Mouse //��(�Ӹ�)
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Mouse"));

	AttackCollision_Foot_Left //���� �ٸ�.
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Foot_L"));
	AttackCollision_Foot_Right //������ �ٸ�.
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Foot_R"));

	AttackCollision_Tail01 //������
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail01"));
	AttackCollision_Tail02 
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail02"));
	AttackCollision_Tail03
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail03"));
	AttackCollision_Tail04
		= CreateDefaultSubobject<USphereComponent>(TEXT("AtkCollision_Tail04"));


	//���� �ݸ��� ����.
	//�켱 ũ�� ����(�������� �޴� ��Ʈ�ڽ��� �� ũ�� 250����/�������� �ִ� ���ùڽ��� 200����)
	HitBoxRadius = 250.0f;
	AttackCollisionRadius = 200.0f;

	//1. �켱 ��Ʈ�ڽ����� ���� Mesh�� ������.
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

	//2. �׸��� ��Ʈ�ڽ����� ũ�⸦ �����Ѵ�.
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

	//3. �׸��� ������ �̺�Ʈ�� �Ҽ� �ְ� �̸� Ű��.
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




	//���⼭ ��Ʈ�ڽ� �ݸ��� ������ ��.
	// 
	// 
	//4.�� ���� �����ݸ������� �޽ÿ� ������.
	AttackCollision_Mouse->SetupAttachment(GetMesh(),HeadBoneName);
	AttackCollision_Foot_Left->SetupAttachment(GetMesh(),LeftFootBoneName);
	AttackCollision_Foot_Right->SetupAttachment(GetMesh(),RightFootBoneName);

	AttackCollision_Tail01->SetupAttachment(GetMesh(),Tail01BoneName);
	AttackCollision_Tail02->SetupAttachment(GetMesh(),Tail02BoneName);
	AttackCollision_Tail03->SetupAttachment(GetMesh(),Tail03BoneName);
	AttackCollision_Tail04->SetupAttachment(GetMesh(),Tail04BoneName);


	//5. �״��� ���� �ݸ����� ũ�⸦ �����Ѵ�.
	AttackCollision_Mouse->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Foot_Left->SetSphereRadius(AttackCollisionRadius - 100);
	AttackCollision_Foot_Right->SetSphereRadius(AttackCollisionRadius - 100);

	AttackCollision_Tail01->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail02->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail03->SetSphereRadius(AttackCollisionRadius);
	AttackCollision_Tail04->SetSphereRadius(AttackCollisionRadius);

	//6. �״��� �����ݸ������� �������̺�Ʈ ���� ���θ� Ų��.
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

	//��Ʈ�ڽ� �ݸ��� ���� ����.
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

void AMyDinoValdo::OnTailAttackBegin() //�������ð���
{
	//���� ���ý�
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnTailAttackEnd() //������������
{
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::OnSpecialAttackBegin() // Ư������ ����(��ȸ������ ���) 
{
	//��� ĸ�� ������Ʈ �������ǰ�.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//�����ε� ������
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//�ٸ��ε� ������.
	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnSpecialAttackEnd() //Ư�� ���� ����.
{
	//ĸ��������Ʈ �ٽ� �浹����.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//�����ε� �����°� ����
	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�ٸ��ε� �����°� ����
	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::OnMouseAttackBegin() //���� ���� ����.
{
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyDinoValdo::OnMouseAttackEnd() //���� ���� ����.
{
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyDinoValdo::BeginPlay()
{
	Super::BeginPlay();

	//Ÿ�Ӷ���.
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
	//ĸ��������Ʈ �ٽ� ������.
	if(GetCapsuleComponent()->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//��� �����ݸ��� ����.
	AttackCollision_Mouse->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision_Foot_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Foot_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision_Tail01->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail02->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail03->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision_Tail04->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�� �� �г���·� ��ȯ.
	bAngry = true;
}

void AMyDinoValdo::DashToSpeicalDash(float TimeLineValue)
{
	float DashPower = 2000.0f;
	//UE_LOG(LogTemp, Display, TEXT("DINOVALDO SPD TEST"));
	DashToPlayerOfTimeLine(TimeLineValue, DashPower);
}


