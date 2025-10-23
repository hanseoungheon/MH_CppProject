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
	//콜리전들
	//먼저 히트박스(디노발드가 맞는 판정의 히트박스)
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Head; //머리

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Chest; //가슴

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Body; //몸통

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Leg_Left; //왼쪽 다리
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Foot_Left; //왼쪽 발

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Leg_Right; //오른쪽 다리.
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Foot_Right; //오른쪽 발.

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail01; //꼬리 1
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail02; //꼬리 2
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail03; //꼬리 3
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HitBox_Tail04; //꼬리 4

	//그 다음 공격박스(디노발드가 공격하는 판정의 히트박스)
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Mouse; //입(머리)

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Foot_Left; //왼쪽 다리.
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Foot_Right; //오른쪽 다리.

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail01; //꼬리1
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail02; //꼬리2
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail03; //꼬리3
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackCollision_Tail04; //꼬리4




};
