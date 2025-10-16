// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunter.h"
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
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	DefaultAttackCheck = 0; // 기본공격시 마다 트리거되서 하나씩 증감되는 변수
	DefaultAttackCombo = (DefaultAttackCheck % 4) + 1; //어택체크를 계산한 기본공격에 쓰일 어택콤보.

	CurrentRot = 90.0f; //YawRotVector에서 90을 곱하면 정확히 입력값에 따라서 바라보는 방향이 YawRotVector에 저장됨.

	RollingSpeed = 750.0f;

	RollingTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("RollingTimeLine"));

}

// Called when the game starts or when spawned
void AMyPlayerHunter::BeginPlay()
{
	Super::BeginPlay();

	if (RollingCurve != nullptr)
	{
		RollingInterpFunction.BindUFunction(this, FName("OnRollingUpdate"));

		RollingTimeLine->AddInterpFloat(RollingCurve, RollingInterpFunction);

		RollingTimeLine->SetLooping(false);
		RollingTimeLine->SetPlayRate(1.0f);

		//항상 시작부분부터 시작.
		//RollingTimeLine->PlayFromStart();
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

ECharacterState AMyPlayerHunter::GetCharacterState() const
{
	return State;
}

void AMyPlayerHunter::SetState(const ECharacterState NewState)
{
	State = NewState;
}

void AMyPlayerHunter::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f))
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (InputValue.X != 0.0f)
		{
			const FVector RightDirection =
				UKismetMathLibrary::GetRightVector(YawRotation);

			AddMovementInput(RightDirection, InputValue.X);
		}

		if (InputValue.Y != 0.0f)
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
		IsBeRun = true;
		float CurrentMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;

		//달리기시 이동속도 2배.
		GetCharacterMovement()->MaxWalkSpeed = CurrentMovementSpeed * 2.0;
	}
	else if (bIsSheathWepaon == false && State == ECharacterState::Battle)
	{
		bIsSheathWepaon = true;

		if (LongSword != nullptr)
		{
			PlayAnimMontage(SheathLongSword_LS, 1.0f, TEXT("Sheath"));
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
	//UE_LOG(LogTemp, Display, TEXT("Is Working"));
	if (LongSword == nullptr)
	{
		return;
	}

	//만약 검을 뽑고있는중이 아니며, 비전투상태일경우. 
	if (bIsDrawWeapon == false && State == ECharacterState::Peace)
	{
		if (MovingSpeed > WalkSpeed)
		{
			//Todo: 달리면서 어택키를 누를시 즉시 발도하면서 공격.
		}
		else
		{
			bIsDrawWeapon = true; //검을 뽑고있는중으로 변경.

			if (LongSword != nullptr)
			{
				PlayAnimMontage(DrawLongSword_LS, 1.0f, TEXT("Draw"));
			}
		}

	}
	else if (State == ECharacterState::Battle) //전투상태일경우.
	{
		if (bIsAttacking == false) //전투중(Battle)에 공격중이 아닐경우.
		{
			bIsAttacking = true; //공격중으로 설정.

			if (LongSword != nullptr)
			{
				switch (DefaultAttackCombo)
				{
				case 1:
					PlayAnimMontage(DefaultAttack_LS, 1.0f, TEXT("DAttack_1"));
					break;

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
	if (LongSword == nullptr || State == ECharacterState::Peace)
	{
		return;
	}

	if (State == ECharacterState::Battle)
	{
		if (bIsAttacking == false) //전투상태이고, 공격중이 아닐경우
		{
			bIsAttacking = true; //공격중 상태로 변경.

			if (LongSword != nullptr)
			{
				PlayAnimMontage(SubAttack_LS, 1.0f, TEXT("SAttack"));

				DefaultAttackCheck = 2;
				DefaultAttackCombo = (DefaultAttackCheck % 4) + 1;
			}
		}
	}
}

void AMyPlayerHunter::StartRolling()
{
	if (bIsRolling == false && bIsAttacking == false) //구르고 있는중이 아니고 공격중이 아니라면!
	{
		bIsRolling = true;

		PlayAnimMontage(RollAnim, 1.0f, TEXT("Rolling"));
	}
}

void AMyPlayerHunter::OnRollingUpdate(float Value)
{
	UE_LOG(LogTemp, Log, TEXT("동작하는지 테스트."));
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

		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Move);

		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Look);

		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &AMyPlayerHunter::BeginRun);

		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMyPlayerHunter::StopRun);

		EnhancedPlayerInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AMyPlayerHunter::StartPickUp);

		EnhancedPlayerInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AMyPlayerHunter::Attack);

		EnhancedPlayerInputComponent->BindAction(IA_SubAttack, ETriggerEvent::Started, this, &AMyPlayerHunter::AttackSub);

		EnhancedPlayerInputComponent->BindAction(IA_Rolling, ETriggerEvent::Triggered, this, &AMyPlayerHunter::StartRolling);
	}

}

