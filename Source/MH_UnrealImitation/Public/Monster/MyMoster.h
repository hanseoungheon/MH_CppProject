// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMonsterState.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "MyMonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyMoster.generated.h"

UCLASS()
class MH_UNREALIMITATION_API AMyMoster : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensing;
	
public:
	// Sets default values for this character's properties
	AMyMoster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DashToFrontOfTimeLine(float TimeLineValue, float DashSpeed);
	void DashToPlayerOfTimeLine(float TimeLineValue, float DashSpeed);

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

public:

	//Getter & Setter
	UFUNCTION(BlueprintCallable, Category = "State")
	EMonsterState GetMonsterState() const
	{
		return State;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetMonsterState(const EMonsterState NewState)
	{
		if (State == EMonsterState::Dead)
		{
			return;
		}

		State = NewState;

		AMyMonsterAIController* MyAIController = Cast<AMyMonsterAIController>(GetController());

		if (MyAIController != nullptr)
		{
			UBlackboardComponent* BB = MyAIController->GetBlackboardComponent();

			if (BB == nullptr)
			{
				return;
			}

			BB->SetValueAsEnum(StateKey,static_cast<uint8>(NewState));
		}
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	EMonsterState GetMonsterPreState() const
	{
		return PreState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetMonsterPreState(const EMonsterState NewPreState)
	{
		PreState = NewPreState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetPatrolRadius() const
	{
		return PatrolRadius;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bAngry = false; //분노했는지 하지않았는지.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float AngryMoment; //분노를 위한 데미지.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState State = EMonsterState::Peace; // 현재상태.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMonsterState PreState = EMonsterState::Peace; //이전 상태 저장용


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 0.0f; // 걷기 스피드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 0.0f; //뛰기 스피드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName TargetPlayerKey = NAME_None; // 타겟플레이어 키(안쓸수도)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FName StateKey = NAME_None; //스테이트 키(안쓸수도)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Hp = 0.0f; //몬스터 체력

	UPROPERTY()
	float TimeLinePrev = 0.0f; //타임라인용 타이머 변수.

	UPROPERTY(EditAnywhere, Category = "Movement")
	float PatrolRadius = 1500.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	EMonsterState DebugState = EMonsterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	class UAnimMontage* RoarMontage = nullptr;
};
