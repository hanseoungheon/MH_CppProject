// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMonsterState.h"
#include "MyCharacterBase.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "MyMonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyMoster.generated.h"

class UAnimMontage;

UCLASS()
class MH_UNREALIMITATION_API AMyMonster : public AMyCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensing;
	
public:
	// Sets default values for this character's properties
	AMyMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	void DashToPlayerOfTimeLine(float TimeLineValue, float DashSpeed);

	UFUNCTION(Category = "Attack")
	void DashEndToTimeLine();

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void Angry();

	//TakeDamage�� �׳� �θ� ���°ɷ�.

	virtual void Dead() override;

	//������ �ֱ�.
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamamge(AActor* Other, float BaseDamage, AController* InstigatorCtrl);

public:

	//Getter & Setter
	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE EMonsterState GetMonsterState() const
	{
		return State;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetMonsterState(const EMonsterState NewState);

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE EMonsterState GetMonsterPreState() const
	{
		return PreState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE void SetMonsterPreState(const EMonsterState NewPreState)
	{
		PreState = NewPreState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE float GetPatrolRadius() const
	{
		return PatrolRadius;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bAngry = false; //�г��ߴ��� �����ʾҴ���.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float AngryMoment; //�г븦 ���� ������.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState State = EMonsterState::Peace; // �������.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState PreState = EMonsterState::Peace; //���� ���� �����


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName TargetPlayerKey = NAME_None; // Ÿ���÷��̾� Ű(�Ⱦ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FName StateKey = NAME_None; //������Ʈ Ű(�Ⱦ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Hp = 0.0f; //���� ü��


	UPROPERTY(EditAnywhere, Category = "Movement")
	float PatrolRadius = 1500.0f;

	float HitBoxRadius = 0.0f;
	float AttackCollisionRadius = 0.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	EMonsterState DebugState = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	UAnimMontage* RoarMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	TArray<UAnimMontage*> AttackMontages;
};
