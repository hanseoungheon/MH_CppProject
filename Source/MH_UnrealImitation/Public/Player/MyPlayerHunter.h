// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyCharacterState.h"
#include "MyPlayerHunter.generated.h"


UCLASS()
class MH_UNREALIMITATION_API AMyPlayerHunter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPSCAM, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPSCAM, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	// Sets default values for this character's properties
	AMyPlayerHunter();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void IsInteract_PickUpWeapon(bool Trigger, AActor* WeaponActor);


	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SpawnDummys();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnLongSwordAndHouse();

	UFUNCTION(BlueprintCallable, Category = "Move")
	void OnRollingUpdate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Move")
	void Rolling();

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToTimeLine(float TimeLineValue,float DashSpeed);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToKiin(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToGanpa(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashEndToTimeLine();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void BeginRun(); //달리기 시작/납도

	void StopRun(); //달리기 멈춤

	void Attack(); //기본공격 강<왼쪽 마우스>(기본)

	void AttackSub(); //기본공격 약<오른쪽 마우스>(기본)

	void SkillAttack(); //컨트롤키(기본)

	void Skill_Special(); //컨트롤키 + 왼쪽클릭 (기본)

	void Skill_Special_Sub(); //컨트롤키 + 우클릭 (기본)

	void Skill_Speical_Roll(); //컨트롤키 + 스페이스바(기본) -> 태도 특납
	
	void StartRolling(); //구르기<스페이스바>(기본)

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void PickUpTheWeapon(FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void StartPickUp();

	void RollRotationChange();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getters & Setters
	UFUNCTION(BlueprintCallable, Category = "State")
	ECharacterState GetCharacterState() const
	{
		return State;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetState(const ECharacterState NewState)
	{
		State = NewState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	ECharacterState GetPrevState() const
	{
		return PrevState;
	}
	
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetPrevState()
	{
		//PrevState에 State를 저장에서 이전 프레임/동작에 사용된 State로 사용.
		PrevState = State;
	}

public:

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Run;
	//UPROPERTY(EditAnywhere, Category = "Input")

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_SubAttack;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Rolling;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Skill;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Skill_Special_Sub;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_ComboCheck;



public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyLongSword* LongSword = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyDummyWeapon* DummyLongSword = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyDummyLSHouse* DummyLSHouse = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHunterCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHasWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsDrawWeapon = false; //무기를 뽑고있는중인간(이제 bIsHanging에서 처리안하고 Enum으로 처리)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsSheathWepaon = false; //무기를 넣고있는 중인가.

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon")
	bool bIsAttacking = false; //공격중인지?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsRolling = false; //구르고 있는 중인지?

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 DefaultAttackCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 DefaultAttackCombo;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState State = ECharacterState::Peace;

	ECharacterState PrevState = ECharacterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool IsBeRun = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float MovingSpeed = 0.0f;

	UPROPERTY()
	float CurrentRot; //플레이어의 현재 방향을 정하는데 쓰이는 실수형 변수.

	UPROPERTY()
	FVector YawRotVector; //플레이어가 바라보는 방향전위를 벡터로 나타낸것.

	UPROPERTY()
	float RollingSpeed; //구르는 속도.

	UPROPERTY()
	float TimeLinePrev; //타임라인 타이머용 변수.

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* DrawLongSword_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* SheathLongSword_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* SheathWalkLongSwrod_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* DefaultAttack_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* SubAttack_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/Movement")
	class UAnimMontage* RollAnim = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* KiinAttck_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* Ganpa_Ls = nullptr;



public:
	//구르기 타임라인.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* RollingTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* RollingCurve = nullptr;




	//마지막 기인 돌진 타임라인.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* KiinDashTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* KiinDashCurve = nullptr;

	//간파 돌진 타임라인.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* GanpaDashTimeLine = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* GanpaDashCurve = nullptr;
protected:
	////구르기 타임라인 변수.
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineFloat InterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent FinishedFunction;



	////기인 마지막 대쉬 타임라인 변수.
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineFloat KiinDashInterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent KiinDashFinishedFunction;



	////간파 돌진 타임라인 변수.
	//UPROPERTY(EditAnywhere, Category = "TiemLine")
	//FOnTimelineFloat GanpaDashInterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent GanpaDashFinishedFunction;
};
