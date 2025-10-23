// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MyMoster.h"
#include "Components/TimelineComponent.h"
#include "MyDinoValdo.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API AMyDinoValdo : public AMyMonster
{
	GENERATED_BODY()
	
public:
	AMyDinoValdo();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnTailAttackBegin();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnTailAttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnSpecialAttackBegin();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnSpecialAttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnMouseAttackBegin();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnMouseAttackEnd();

protected:
	virtual void BeginPlay() override;

	virtual void Angry() override;

	UFUNCTION(Category = "Attack")
	void DashToSpeicalDash(float TimeLineValue);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* SpecialDashTimeline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* SpecialDashCurve = nullptr;
 
protected:
	//�ݸ�����
	//���� ��Ʈ�ڽ�(���ߵ尡 �´� ������ ��Ʈ�ڽ�)
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Head; //�Ӹ�

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Chest; //����

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Body; //����

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Leg_Left; //���� �ٸ�
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Foot_Left; //���� ��

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Leg_Right; //������ �ٸ�.
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Foot_Right; //������ ��.

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail01; //���� 1
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail02; //���� 2
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail03; //���� 3
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail04; //���� 4

	//�� ���� ���ݹڽ�(���ߵ尡 �����ϴ� ������ ��Ʈ�ڽ�)
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Mouse; //��(�Ӹ�)

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Foot_Left; //���� �ٸ�.
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Foot_Right; //������ �ٸ�.

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail01; //����1
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail02; //����2
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail03; //����3
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail04; //����4




};
