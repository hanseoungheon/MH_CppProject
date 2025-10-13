// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunter.h"
#include "MyLongSword.h"
#include "MyDummyWeapon.h"
#include "MyDummyLSHouse.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	//WalkSpeed는 헤더에 선언해 놓은 Float 변수입니다.
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	CameraBoom
		= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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
		if (bHasWeapon == false) //무기를 가지고 있지 않을때만 벗어날때 SetOwner취소하기.
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


// Called when the game starts or when spawned
void AMyPlayerHunter::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (State != ECharacterState::Peace)
	{
		return;
	}

	IsBeRun = true;
	float CurrentMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	//달릴시 80% 이동속도 버프
	GetCharacterMovement()->MaxWalkSpeed = CurrentMovementSpeed * 2.0;
}

void AMyPlayerHunter::StopRun()
{
	if (State != ECharacterState::Peace)
	{
		return;
	}

	IsBeRun = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyPlayerHunter::Attack()
{
	//UE_LOG(LogTemp, Display, TEXT("Is Working"));
	if (LongSword != nullptr)
	{
		//태도 무기공격 구현.
		if (bIsHanging == true)
		{
			PlayAnimMontage(DrawLongSword, 1.0f, TEXT("Draw"));
		}
		else
		{

		}
	}
}


void AMyPlayerHunter::PickUpTheWeapon(FName SocketName)
{
	if (bHasWeapon == false && bHunterCanInteract == true)
	{
		//만약 무기가 없는 상태고, 상호작용이 가능한 상태라면?

		if (LongSword != nullptr)
		{
			bHasWeapon = true;
			//태도를 플레이어에게 붙힘.
			LongSword->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,SocketName);
		}


		//태도의 충돌구체를 비활성화함.
		USphereComponent* LongSwordSphereComponent = 
			Cast<USphereComponent>(LongSword->SphereCollision);

		if (LongSwordSphereComponent != nullptr)
		{
			LongSwordSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//LongSword->SphereCollision->SetGenerateOverlapEvents(false);
			//LongSword->SphereCollision->SetNotifyRigidBodyCollision(false);
		}

		//더미무기 활성화.
		SpawnDummys();

		//메기 활성화.
		bIsHanging = true;

		//이제 Visible설정하자. 그냥 매번 이렇게 불러오는게 맘 편할듯.
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

	//UE_LOG(LogTemp, Display, TEXT("Is Working"));
	//여기부터 대검 등 다른 무기 넣으면 될듯?
	//if(ActorHasTag("GreatSword"))...
}

// Called every frame
void AMyPlayerHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

		EnhancedPlayerInputComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Attack);
	}

}

