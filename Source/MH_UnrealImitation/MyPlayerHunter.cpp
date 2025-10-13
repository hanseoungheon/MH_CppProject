// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHunter.h"
#include "MyLongSword.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputAction.h"

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

	//WalkSpeed�� ����� ������ ���� Float �����Դϴ�.
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
		if (bHasWeapon == false) //���⸦ ������ ���� �������� ����� SetOwner����ϱ�.
		{
			LS->SetOwner(nullptr);
		}
	}
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
	IsBeRun = true;
	float CurrentMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	//�޸��� 80% �̵��ӵ� ����
	GetCharacterMovement()->MaxWalkSpeed = CurrentMovementSpeed * 2.0;


}

void AMyPlayerHunter::StopRun()
{
	IsBeRun = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyPlayerHunter::PickUpTheWeapon(FName SocketName)
{
	if (bHasWeapon == false && bHunterCanInteract == true)
	{
		//���� ���Ⱑ ���� ���°�, ��ȣ�ۿ��� ������ ���¶��?
		bHasWeapon = true;

		if (LongSword != nullptr)
		{
			//�µ��� �÷��̾�� ����.
			LongSword->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,SocketName);
		}

		//�µ��� �浹��ü�� ��Ȱ��ȭ��.
		if (LongSword->SphereCollision != nullptr)
		{
			LongSword->SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			LongSword->SphereCollision->SetGenerateOverlapEvents(false);
			LongSword->SphereCollision->SetNotifyRigidBodyCollision(false);
		}

		//�ޱ� Ȱ��ȭ.
		bIsHanging = true;
	}
}

void AMyPlayerHunter::StartPickUp()
{
	if (LongSword != nullptr)
	{
		FName LongSwordSocketName = TEXT("LongSword");
		PickUpTheWeapon(LongSwordSocketName);
	}

	//������� ��� �� �ٸ� ���� ������ �ɵ�?
	//if(GreatSword != nullptr)...
}

// Called every frame
void AMyPlayerHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Move);

		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayerHunter::Look);

		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &AMyPlayerHunter::BeginRun);

		EnhancedPlayerInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMyPlayerHunter::StopRun);

		EnhancedPlayerInputComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AMyPlayerHunter::StartPickUp);
	}

}

