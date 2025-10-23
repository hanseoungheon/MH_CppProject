// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "InputActionValue.h"
#include "MyCharacterBase.h"
#include "GameFramework/Character.h"
#include "MyCharacterState.h"
#include "MyPlayerHunter.generated.h"


UCLASS()
class MH_UNREALIMITATION_API AMyPlayerHunter : public AMyCharacterBase
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



	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnHunterAttackCheckBegin();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnHunterAttackCheckEnd();

	UFUNCTION(BlueprintCallable, Category = "Move")
	void OnRollingUpdate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Move")
	void Rolling();


	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToKiin(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToGanpa(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToBreakHead(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashToIaiSkill(float TimeLineValue);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DashEndToTimeLine();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void BeginRun(); //�޸��� ����/����

	void StopRun(); //�޸��� ����

	void Attack(); //�⺻���� ��<���� ���콺>(�⺻)

	void AttackSub(); //�⺻���� ��<������ ���콺>(�⺻)

	void SkillAttack(); //��Ʈ��Ű(�⺻)

	void Skill_Special(); //��Ʈ��Ű + ����Ŭ�� (�⺻)

	void Skill_Special_Sub(); //��Ʈ��Ű + ��Ŭ�� (�⺻)

	void Skill_Speical_Roll(); //��Ʈ��Ű + �����̽���(�⺻) -> �µ� Ư��
	
	void StartRolling(); //������<�����̽���>(�⺻)

	void SetHunterRoataion();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void PickUpTheWeapon(FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void StartPickUp();

	void RollRotationChange();

	virtual void Dead() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getters & Setters
	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE ECharacterState GetCharacterState() const
	{
		return State;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE void SetState(const ECharacterState NewState)
	{
		State = NewState;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE ECharacterState GetPrevState() const
	{
		return PrevState;
	}
	
	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE void SetPrevState()
	{
		//PrevState�� State�� ���忡�� ���� ������/���ۿ� ���� State�� ���.
		PrevState = State;
	}

	UFUNCTION(BlueprintCallable, Category = "Vector")
	FORCEINLINE void SetYawRotVector(const FVector NewVector)
	{
		YawRotVector = NewVector;
	}

	FORCEINLINE bool GetIsBeRun() const
	{
		return IsBeRun;
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
	class UInputAction* IA_Skill_Special;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Skill_Special_Sub;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Skill_Speical_Roll;

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
	bool bIsDrawWeapon = false; //���⸦ �̰��ִ����ΰ�(���� bIsHanging���� ó�����ϰ� Enum���� ó��)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsSheathWepaon = false; //���⸦ �ְ��ִ� ���ΰ�.

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon")
	bool bIsAttacking = false; //����������?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsRolling = false; //������ �ִ� ������?

	bool bIsCanMove = true; //������ �� ���»�������?

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 DefaultAttackCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 DefaultAttackCombo;

	//ȸ�ǿ� ���� ����.
	UPROPERTY(EditAnywhere, Category = "Dodge")
	bool Dodge_Roll = false;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState State = ECharacterState::Peace;

	ECharacterState PrevState = ECharacterState::Peace;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool IsBeRun = false;

	UPROPERTY()
	float CurrentRot; //�÷��̾��� ���� ������ ���ϴµ� ���̴� �Ǽ��� ����.

	UPROPERTY()
	FVector YawRotVector; //�÷��̾ �ٶ󺸴� ���������� ���ͷ� ��Ÿ����.

	UPROPERTY()
	float RollingSpeed; //������ �ӵ�.

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* BreakHead_LS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* IaiAttack_LS = nullptr;




public:
	//������ Ÿ�Ӷ���.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* RollingTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* RollingCurve = nullptr;




	//������ ���� ���� Ÿ�Ӷ���.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* KiinDashTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* KiinDashCurve = nullptr;

	//���� ���� Ÿ�Ӷ���.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* GanpaDashTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* GanpaDashCurve = nullptr;


	//�������� Ÿ�Ӷ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TiemLine")
	UTimelineComponent* BreakHeadTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TiemLine")
	UCurveFloat* BreadHeadCurve = nullptr;

	//�ɾ� �ߵ� ���� ���� Ÿ�Ӷ���.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* IaiDashTimeLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* IaiDashCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* IaiDefaultAttackDashTimeLine = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TiemLine")
	UCurveFloat* IaiDefaultAttackDashCurve = nullptr;


protected:
	////������ Ÿ�Ӷ��� ����.
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineFloat InterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent FinishedFunction;



	////���� ������ �뽬 Ÿ�Ӷ��� ����.
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineFloat KiinDashInterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent KiinDashFinishedFunction;



	////���� ���� Ÿ�Ӷ��� ����.
	//UPROPERTY(EditAnywhere, Category = "TiemLine")
	//FOnTimelineFloat GanpaDashInterpFunction;
	//UPROPERTY(EditAnywhere, Category = "TimeLine")
	//FOnTimelineEvent GanpaDashFinishedFunction;
};
