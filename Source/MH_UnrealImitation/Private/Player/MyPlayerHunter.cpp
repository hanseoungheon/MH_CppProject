// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerHunter.h"
#include "Weapon/MyLongSword.h"
#include "Weapon/MyDummyWeapon.h"
#include "Weapon/MyDummyLSHouse.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputAction.h"
#include "Animation/AnimMontage.h"
#include "MyComponent/MyDamageReceiver.h"
#include "GameFramework/Controller.h"

// Sets default values
AMyPlayerHunter::AMyPlayerHunter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(41.2f, 96.0f);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	//WalkSpeed를 통해 캐릭터의 기본 이동속도 설정.
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	//카메라 설정.
	CameraBoom
		= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	DefaultAttackCheck = 0; // 기본공격시 마다 트리거되서 하나씩 증감되는 변수
	DefaultAttackCombo = (DefaultAttackCheck % 4) + 1; //어택체크를 계산한 기본공격에 쓰일 어택콤보.

	CurrentRot = 90.0f; //YawRotVector에서 90을 곱하면 정확히 입력값에 따라서 바라보는 방향이 YawRotVector에 저장됨.

	RollingSpeed = 700.0f; //구르기 속도

	TimeLinePrev = 0.0f; //타임라인 체크 변수 초기화.

	//타임라인들 생성.
	RollingTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("RollingTimeLine"));
	KiinDashTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("KiinDashTimeLine"));
	GanpaDashTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("GanpaDashTimeLine"));
	BreakHeadTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("BreakHeadTimeLine"));
	IaiDashTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("IaiDashTimeline"));

}

// Called when the game starts or when spawned
void AMyPlayerHunter::BeginPlay()
{
	Super::BeginPlay();

	DamageReceiver = FindComponentByClass<UMyDamageReceiver>(); //에디터에서 추가할거임.

	if (DamageReceiver != nullptr)
	{
		DamageReceiver->OnDead.AddDynamic(this, &AMyPlayerHunter::OnPlayerDead);
		DamageReceiver->OnHealthChanged.AddDynamic(this, &AMyPlayerHunter::PrintHelath);
	}

	//구르기 타임라인 설정.
	if (RollingCurve != nullptr)
	{
		FOnTimelineFloat RollingInterpFunction;

		RollingInterpFunction.BindUFunction(this, FName("OnRollingUpdate"));
		RollingTimeLine->AddInterpFloat(RollingCurve, RollingInterpFunction);

		RollingTimeLine->SetLooping(false);
		RollingTimeLine->SetPlayRate(1.0f);

		//항상 시작부분부터 시작.
		//RollingTimeLine->PlayFromStart();
	}

	//기인베기 돌진 타임라인 설정.
	if (KiinDashTimeLine != nullptr)
	{
		FOnTimelineFloat KiinDashInterpFunction;
		FOnTimelineEvent KiinDashFinishedFunction;

		KiinDashInterpFunction.BindUFunction(this, FName("DashToKiin"));
		KiinDashTimeLine->AddInterpFloat(KiinDashCurve, KiinDashInterpFunction);

		KiinDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		KiinDashTimeLine->SetTimelineFinishedFunc(KiinDashFinishedFunction);

		KiinDashTimeLine->SetLooping(false);
		KiinDashTimeLine->SetPlayRate(1.0f);
	}

	//간파베기 돌진 타임라인 설정.
	if (GanpaDashTimeLine != nullptr)
	{
		FOnTimelineFloat GanpaDashInterpFunction;
		FOnTimelineEvent GanpaDashFinishedFunction;

		GanpaDashInterpFunction.BindUFunction(this, FName("DashToGanpa"));
		GanpaDashTimeLine->AddInterpFloat(GanpaDashCurve, GanpaDashInterpFunction);

		GanpaDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		GanpaDashTimeLine->SetTimelineFinishedFunc(GanpaDashFinishedFunction);

		GanpaDashTimeLine->SetLooping(false);
		GanpaDashTimeLine->SetPlayRate(1.0f);
	}

	//기인찌르기(투구깨기) 타임라인 설정
	if (BreakHeadTimeLine != nullptr)
	{
		FOnTimelineFloat BreakHeadDashInterpFunction;
		FOnTimelineEvent BreadHeadDashFinishedFunction;

		BreakHeadDashInterpFunction.BindUFunction(this, FName("DashToBreakHead"));
		BreakHeadTimeLine->AddInterpFloat(BreadHeadCurve, BreakHeadDashInterpFunction);

		BreadHeadDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		BreakHeadTimeLine->SetTimelineFinishedFunc(BreadHeadDashFinishedFunction);

		BreakHeadTimeLine->SetLooping(false);
		BreakHeadTimeLine->SetPlayRate(1.0f);
	}

	//앉아발도 기인베기 타임라인설정

	if (IaiDashTimeLine != nullptr)
	{
		FOnTimelineFloat IaiSkillDashInterpFunction;
		FOnTimelineEvent IaiSkillDashFinishedFunction;

		IaiSkillDashInterpFunction.BindUFunction(this, FName("DashToIaiSkill"));
		IaiDashTimeLine->AddInterpFloat(IaiDashCurve, IaiSkillDashInterpFunction);

		IaiSkillDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		IaiDashTimeLine->SetTimelineFinishedFunc(IaiSkillDashFinishedFunction);

		IaiDashTimeLine->SetLooping(false);
		IaiDashTimeLine->SetPlayRate(1.0f);
	}
}
	
void AMyPlayerHunter::IsInteract_PickUpWeapon(bool Trigger, AActor* WeaponActor)
{
	AMyLongSword* LS = Cast<AMyLongSword>(WeaponActor);

	if (LS == nullptr)
	{
		return;
	}

	if (Trigger == true)
	{
		LS->SetOwner(this);
		LongSword = LS;
	}

	else //Trigger == false
	{
		if (bHasWeapon == false) //만약 무기를 들고있지 않으면 SetOwner를 nullptr로 설정.(주인해제)
		{
			LS->SetOwner(nullptr);
		}
	}
}

void AMyPlayerHunter::SpawnDummys()
{
	if (LongSword != nullptr)
	{
		SpawnLongSwordAndHouse();
	}
}

//데미지를 받았을 때
float AMyPlayerHunter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Dodge_Roll == true) //구르기상태면 피해입지 않고 바로 종료.
	{
		return 0.0f;
	}

	if (LongSword != nullptr)
	{
		if (LongSword->Dodge_Ganpa == true)
		{
			UE_LOG(LogTemp, Display, TEXT("간파베기로 씹기 성공"));
			//간파베기에 성공 시 기인레벨 한번에 끝까지.
			LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel4;
			return 0.0f; //그리고 피해입지않고 바로 종료.
		}

		if (LongSword->Dodge_Iai == true)
		{
			UE_LOG(LogTemp, Display, TEXT("특납 씹기 성공 발도 간지당"));
			//특납으로 피할시 즉시 기인레벨 업그레이드.
			switch (LongSword->KiinLevel)
			{
			case ELongSwordLevel::LSLevel0:
				LongSword->KiinLevel = ELongSwordLevel::LSLevel1;
				break;

			case ELongSwordLevel::LSLevel1:
				LongSword->KiinLevel = ELongSwordLevel::LSLevel2;
				break;

			case ELongSwordLevel::LSLevel2:
				LongSword->KiinLevel = ELongSwordLevel::LSLevel3;
				break;

			case ELongSwordLevel::LSLevel3:
				LongSword->KiinLevel = ELongSwordLevel::LSLevel3;
				break;
			}

			return 0.0f; //그리고 피해입지않고 바로 종료.
		}
	}

	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageReceiver->OnDamageReceived(FinalDamage);

	return FinalDamage;
}

void AMyPlayerHunter::OnPlayerDead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	State = ECharacterState::Dead;
	
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;

	StopAnimMontage();
}

void AMyPlayerHunter::PrintHelath(float HealthPower, float MaxHealthPower)
{
	UE_LOG(LogTemp, Display, TEXT("Max Player Health :%f\n\n"), DamageReceiver->GetMaxHealthPower());
	UE_LOG(LogTemp, Display, TEXT("Current Player Health : %f\n\n"), DamageReceiver->GetHealthPower());
}

void AMyPlayerHunter::OnHunterAttackCheckBegin()
{
	if (LongSword != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Hunter AttackBegin"));
		LongSword->OnAttackToBegin();
	}
}

void AMyPlayerHunter::OnHunterAttackCheckEnd()
{
	if (LongSword != nullptr)
	{
		LongSword->OnAttackToEnd();
	}
}

void AMyPlayerHunter::Move(const FInputActionValue& Value)
{
	if (State == ECharacterState::Dead)
	{
		return;
	}

	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f))
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (InputValue.X != 0.0f && bIsCanMove == true) //공격중이 아닐때만 이동 가능하게 하지만 일단 에디터에서 해보자
		{
			const FVector RightDirection =
				UKismetMathLibrary::GetRightVector(YawRotation);

			AddMovementInput(RightDirection, InputValue.X);
		}

		if (InputValue.Y != 0.0f && bIsCanMove == true) //공격중이 아닐때만 이동 가능하게 하지만 일단 에디터에서 해보자
		{
			const FVector ForwardVector =
				YawRotation.Vector();

			AddMovementInput(ForwardVector, InputValue.Y);
		}

		//FVector인 YawRotVector에 90.0f인 CurrentRot에 입력값 축들을 곱해서 입력값에 따라 현재 바라보고있는 값이
		//방향전위벡터인 YawRotVector에 저장이됨.
		YawRotVector = FVector(InputValue.X * CurrentRot, InputValue.Y * CurrentRot,0.0f);

		//UE_LOG(LogTemp, Display, TEXT("방향전위벡터의 값 = X: %f, Y: %f"), YawRotVector.X, YawRotVector.Y);
	}
}

void AMyPlayerHunter::Look(const FInputActionValue& Value)
{
	if (State == ECharacterState::Dead)
	{
		return;
	}

	FVector2D InputValue = Value.Get<FVector2D>();

	if (InputValue.X != 0.0f)
	{
		AddControllerYawInput(InputValue.X);
	}

	if (InputValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputValue.Y);
	}
}

void AMyPlayerHunter::BeginRun()
{

	if (State == ECharacterState::Peace)
	{
		//발도상태에서 달리기시 
		IsBeRun = true;
		float CurrentMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;

		//달리기시 이동속도 2배.
		GetCharacterMovement()->MaxWalkSpeed = CurrentMovementSpeed * 2.0;
	}
	
	if (bIsSheathWepaon == false && State == ECharacterState::Battle)
	{
		bIsSheathWepaon = true;

		if (LongSword != nullptr)
		{
			//달리고 있는상태에서 넣는동작 추가해야할듯?
			if (MovingSpeed == 0.0f) //움직임이 없을 시.
			{
				//그냥 자동으로 움직이게 하는것도 낫배드.
				PlayAnimMontage(SheathLongSword_LS, 1.0f, TEXT("Sheath"));
			}
			else
			{
				PlayAnimMontage(SheathWalkLongSwrod_LS, 1.0f, TEXT("SheathWalk"));
			}
		}
	}

}

void AMyPlayerHunter::StopRun()
{
	IsBeRun = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyPlayerHunter::Attack()	
{
	//UE_LOG(LogTemp, Display, TEXT("Why Not Working?"));
	//만약 검을 뽑고있는중이 아니며, 비전투상태일경우. 
	if (bIsDrawWeapon == false && State == ECharacterState::Peace)
	{
		//UE_LOG(LogTemp, Display, TEXT("일단 첫번쨰 If문까지는 들어왔음"));

		if (MovingSpeed > WalkSpeed)
		{
			//Todo: 달리면서 어택키를 누를시 즉시 발도하면서 공격.
		}
		else
		{
			bIsDrawWeapon = true; //검을 뽑고있는중으로 변경.
			//UE_LOG(LogTemp, Display, TEXT("여기까지만 되면 LongSword가 NUll인거임"));
			if (LongSword != nullptr)
			{
				PlayAnimMontage(DrawLongSword_LS, 1.0f, TEXT("Draw"));
				//UE_LOG(LogTemp, Display, TEXT("몽타주 재생까지는 들어왔음?"));
			}
		}

	}
	else if (State == ECharacterState::Battle) //전투상태일경우.
	{
		if (bIsAttacking == false) //전투중(Battle)에 공격중이 아닐경우.
		{
			//RollRotationChange();
			bIsAttacking = true; //공격중으로 설정.

			if (LongSword != nullptr)
			{	
				//PrevState = State;
				//State = ECharacterState::Attack;
				switch (DefaultAttackCombo)
				{
				case 1:
				case 2:
					PlayAnimMontage(DefaultAttack_LS, 1.0f, TEXT("DAttack_1"));
					break;

				case 3:
					PlayAnimMontage(DefaultAttack_LS, 1.0f, TEXT("DAttack_2"));
					break;

				case 4:
					PlayAnimMontage(DefaultAttack_LS, 1.0f, TEXT("DAttack_1"));
					break;

				default:
					break;
				}

				DefaultAttackCheck++;
				DefaultAttackCombo = (DefaultAttackCheck % 4) + 1;
			}
		}
	}
}

void AMyPlayerHunter::AttackSub()
{
	if (State == ECharacterState::Peace)
	{
		return;
	}

	if (State == ECharacterState::Battle)
	{
		if (bIsAttacking == false) //전투상태이고, 공격중이 아닐경우
		{
			bIsAttacking = true; //공격중 상태로 변경.

			//RollRotationChange();
			if (LongSword != nullptr)
			{
				PlayAnimMontage(SubAttack_LS, 1.0f, TEXT("SAttack"));

				DefaultAttackCheck = 2;
				DefaultAttackCombo = (DefaultAttackCheck % 4) + 1;
			}
		}
	}
}

void AMyPlayerHunter::SkillAttack()
{
	if (State == ECharacterState::Peace)
	{
		return;
	}

	if (State == ECharacterState::Battle)
	{
		if (bIsAttacking == false)
		{
			bIsAttacking = true;

			if (LongSword != nullptr)
			{
				//기인베기 실행.

				//현재 기인베기공격이 어떤 단계인지 가져옴.
				EKiinAttackLevel LSKiinAttackLevel = LongSword->KiinSkillLevel;

				switch (LSKiinAttackLevel) //스위치를 통해 실행.
				{
				case EKiinAttackLevel::KIINLevel1: //기인레벨이 1이면
					LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel2;//기인레벨2으로 바꿈
					PlayAnimMontage(KiinAttck_LS, 1.0f, TEXT("Kiin1"));
					break;

				case EKiinAttackLevel::KIINLevel2: //기인레벨이 2이면
					LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel3; //기인레벨 3으로 바꿈
					PlayAnimMontage(KiinAttck_LS, 1.0f, TEXT("Kiin2"));
					break;

				case EKiinAttackLevel::KIINLevel3:
					LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel4;
					PlayAnimMontage(KiinAttck_LS, 1.0f, TEXT("Kiin3"));
					break;

				case EKiinAttackLevel::KIINLevel4:
					RollRotationChange();
					LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel1;
					PlayAnimMontage(KiinAttck_LS, 1.0f, TEXT("Kiin4"));
					break;
				}
			}
		}
	}

	if (State == ECharacterState::Iai)
	{
		if (bIsAttacking == false)
		{
			bIsAttacking = true;

			if (LongSword != nullptr)
			{
				PlayAnimMontage(IaiAttack_LS, 1.0f, TEXT("IaiAttack"));
			}
		}
	}
}

void AMyPlayerHunter::Skill_Special()
{
	if (State == ECharacterState::Peace || State == ECharacterState::Dead)
	{
		return;
	}

	if (State == ECharacterState::Battle)
	{
		RollRotationChange();
		
		if (LongSword != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("투구깨기 테스트"));
			if (bIsAttacking == false)
			{
				bIsAttacking = true;
				PlayAnimMontage(BreakHead_LS, 1.0f, TEXT("ReadyBreakHead"));
			}
		}
	}
}

void AMyPlayerHunter::Skill_Special_Sub()
{

	if (State == ECharacterState::Peace || State == ECharacterState::Dead)
	{
		return;
	}
	
	if (State == ECharacterState::Battle)
	{
		RollRotationChange(); //회전하기.

		if (LongSword != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("간파베기 테스트."));
			if (bIsAttacking == false)
			{
				bIsAttacking = true;
				PlayAnimMontage(Ganpa_Ls, 1.0f, TEXT("Parring"));

				//LongSword->KiinSkillLevel = EKiinAttackLevel::KIINLevel4;
			}
		}

	}
}

void AMyPlayerHunter::Skill_Speical_Roll()
{
	if (State == ECharacterState::Peace || State == ECharacterState::Dead)
	{
		return;
	}

	if (State == ECharacterState::Battle)
	{
		RollRotationChange();
		if (LongSword != nullptr)
		{
			if (bIsAttacking == false)
			{
				UE_LOG(LogTemp, Display, TEXT("특수 납도 테스트"));
				//우선 이전 상태를 저장
				PrevState = State;

				//특수 "납도"이므로 납도상태로 전환.
				State = ECharacterState::Sheath;

				//특납 몽타주 애니메이션 실행.
				PlayAnimMontage(IaiAttack_LS, 1.0f, TEXT("Iai"));
			}
		}
	}
}

void AMyPlayerHunter::StartRolling()
{
	if (bIsRolling == false && bIsAttacking == false) //구르고 있는중이 아니고 공격중이 아니라면!
	{
		if (YawRotVector.Y == 90.0f //만약에 움직임 방향전위가 앞이거나, 앞왼/앞오 동시에 일경우 앞구르기 시전. 
			|| YawRotVector.Y == 90.0f && YawRotVector.X == 90.0f
			|| YawRotVector.Y == 90.0f && YawRotVector.X == -90.0f)
		{
			bIsRolling = true;

			//각도 변경해주는 함수.
			RollRotationChange();
			PlayAnimMontage(RollAnim, 1.0f, TEXT("Rolling_F"));
		}
		else if (YawRotVector.Y == -90.0f //만약에 움직임 방향전위가 뒤거나, 뒤왼/뒤오 동시에일 경우 뒷구르기 시전.
			|| YawRotVector.Y == -90.0f && YawRotVector.X == 90.0f
			|| YawRotVector.Y == -90.0f && YawRotVector.X == -90.0f)
		{
			bIsRolling = true;
			//여기서 각도 변경.

			//각도 변경해주는 함수.
			RollRotationChange();

			PlayAnimMontage(RollAnim, 1.0f, TEXT("Rolling_F"));
		}
		else if (YawRotVector.X == -90.0f && YawRotVector.Y == 0.0f) //만약 움직임 방향전위가 왼쪽이고 앞뒤 방향전위가 0일경우
		{
			bIsRolling = true;
			
			RollRotationChange();

			PlayAnimMontage(RollAnim, 1.0f, TEXT("Rolling_F"));
		}
		else if (YawRotVector.X == 90.0f && YawRotVector.Y == 0.0f) //만약 움직임 방향전위가 오른쪽이고 앞뒤 방향전위가 0일경우
		{
			bIsRolling = true;
			
			RollRotationChange();

			PlayAnimMontage(RollAnim, 1.0f, TEXT("Rolling_F"));
		}
	}
}

void AMyPlayerHunter::SetHunterRoataion()
{
	UE_LOG(LogTemp, Display, TEXT("테스트"));

	YawRotVector = FVector(0.0f, 0.0f, 0.0f);
}

void AMyPlayerHunter::OnRollingUpdate(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("동작하는지 테스트."));
	Rolling();
}

void AMyPlayerHunter::Rolling()
{
	//const float Speed = RollingSpeed * GetActorForwardVector()

	//Z축으로 중력의 값이 저장된 flaot 값.
	//땅에 떠있으면 중력이 적용.
	const float KeepZ = GetCharacterMovement()->IsMovingOnGround() ? 0.0f 
		: GetCharacterMovement()->GetGravityZ();

	GetCharacterMovement()->Velocity = (GetActorForwardVector() * RollingSpeed);
	GetCharacterMovement()->Velocity.Z = KeepZ;

}



void AMyPlayerHunter::DashToTimeLine(float TimeLineValue, float DashSpeed)
{
	FVector DashLocation;

	float CurrentTimePrev = TimeLineValue - TimeLinePrev;

	CurrentTimePrev = CurrentTimePrev * DashSpeed;

	DashLocation = GetActorForwardVector() * CurrentTimePrev;

	AddActorWorldOffset(DashLocation, true);

	TimeLinePrev = TimeLineValue;
}

void AMyPlayerHunter::DashToKiin(float TimeLineValue)
{
	float KiinDashPower = 500.0f;
	DashToTimeLine(TimeLineValue, KiinDashPower);
}

void AMyPlayerHunter::DashToGanpa(float TimeLineValue)
{
	float GanpaDashPower = 400.0f;
	DashToTimeLine(TimeLineValue, GanpaDashPower);
}

void AMyPlayerHunter::DashToBreakHead(float TimeLineValue)
{
	float BreakHeadDashPower = 500.0f;
	DashToTimeLine(TimeLineValue, BreakHeadDashPower);
}

void AMyPlayerHunter::DashToIaiSkill(float TimeLineValue)
{
	float IaiSkillDashPower = 1000.0f;
	DashToTimeLine(TimeLineValue, IaiSkillDashPower);
}

void AMyPlayerHunter::DashEndToTimeLine()
{
	TimeLinePrev = 0.0f;
}

void AMyPlayerHunter::PickUpTheWeapon(FName SocketName)
{
	if (bHasWeapon == false && bHunterCanInteract == true)
	{
		//무기를 가지고있지 않고, 상호작용 할 수 있는 상태일경우.

		if (LongSword != nullptr)
		{
			bHasWeapon = true;

			//무기를 붙힘.
			LongSword->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,SocketName);
		}


		//태도의 구체 콜리전에 캐스팅.
		USphereComponent* LongSwordSphereComponent = 
			Cast<USphereComponent>(LongSword->SphereCollision);

		if (LongSwordSphereComponent != nullptr)
		{
			LongSwordSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//LongSword->SphereCollision->SetGenerateOverlapEvents(false);
			//LongSword->SphereCollision->SetNotifyRigidBodyCollision(false);
		}

		//더미 무기들 생성.
		SpawnDummys();


		//무기들 Visible 설정.
		if (LongSword != nullptr)
		{
			LongSword->SetVisibleWeapon();
		}

		if (DummyLongSword != nullptr)
		{
			DummyLongSword->SetVisibleDummy();
		}

		if (DummyLSHouse != nullptr)
		{
			DummyLSHouse->SetVisibleLSHouse();
		}
	}
}

void AMyPlayerHunter::StartPickUp()
{
	if (LongSword != nullptr)
	{
		FName LongSwordSocketName = TEXT("LongSword");
		PickUpTheWeapon(LongSwordSocketName);
	}
}

void AMyPlayerHunter::RollRotationChange()
{

	//if (IsRootMotionActive()) return;                 // 루트모션 중 회전 금지 (권장)
	if (YawRotVector.IsNearlyZero(0.01f)) 
		return;     // ✅ 입력 없으면 회전하지 않음

	//현재 카메라의 각도를 가져와서 저장.
	FRotator CurrentCamRot = GetControlRotation();

	//회전할 각도의 Pitch(Y값)
	float NewPitch = YawRotVector.Y + CurrentCamRot.Pitch;
	//회전할 각도의 Yaw(Z값)
	float NewYaw = YawRotVector.X + CurrentCamRot.Yaw;

	//새로운 각도
	FRotator NewRot = FRotator(NewPitch, NewYaw,CurrentCamRot.Roll);

	SetActorRotation(NewRot);
}

// Called every frame
void AMyPlayerHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovingSpeed = GetVelocity().Size2D(); // == FVector length XY


	//if (LongSword != nullptr)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("Not NULL"));
	//}
	//else if (LongSword == nullptr)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("Is NULL"));
	//}

	UE_LOG(LogTemp, Display, TEXT("방향전위벡터의 값 = X: %f, Y: %f"), YawRotVector.X, YawRotVector.Y);
}

// Called to bind functionality to input
void AMyPlayerHunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedPlayerInputComponent != nullptr)
	{
		APlayerController* PlayerController =
			Cast<APlayerController>(GetController());

		if (PlayerController != nullptr)
		{
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubSystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
				(PlayerController->GetLocalPlayer());

			EnhancedSubSystem->AddMappingContext(IMC_Player, 1);
		}
		ensureMsgf(IA_Interact, TEXT("IA_Interact is NULL"));

		//특수서브스킬사용(태도: 간파베기)
		EnhancedPlayerInputComponent->BindAction(IA_Skill_Special_Sub, ETriggerEvent::Started, this, &AMyPlayerHunter::Skill_Special_Sub);
		//특수 스킬 사용(태도: 기인찌르기->투구깨기)
		EnhancedPlayerInputComponent->BindAction(IA_Skill_Special, ETriggerEvent::Started, this, &AMyPlayerHunter::Skill_Special);
		//특수기 사용(태도 특납)
		EnhancedPlayerInputComponent->BindAction(IA_Skill_Speical_Roll, ETriggerEvent::Started, this, &AMyPlayerHunter::Skill_Speical_Roll);

		//움직임.
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Move);
		//WASD에서 뗄때
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMyPlayerHunter::SetHunterRoataion);
		//마우스로 시선움직이기.
		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Look);
		//달리기 시작
		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &AMyPlayerHunter::BeginRun);
		//달리기 종료
		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMyPlayerHunter::StopRun);
		//상호작용키
		EnhancedPlayerInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AMyPlayerHunter::StartPickUp);
		//구르기
		EnhancedPlayerInputComponent->BindAction(IA_Rolling, ETriggerEvent::Triggered, this, &AMyPlayerHunter::StartRolling);

		//강공격키 
		EnhancedPlayerInputComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Attack);
		//약공격키
		EnhancedPlayerInputComponent->BindAction(IA_SubAttack, ETriggerEvent::Triggered, this, &AMyPlayerHunter::AttackSub);
		//스킬사용(태도: 기인베기)
		EnhancedPlayerInputComponent->BindAction(IA_Skill, ETriggerEvent::Triggered, this, &AMyPlayerHunter::SkillAttack);

	
	}

}

