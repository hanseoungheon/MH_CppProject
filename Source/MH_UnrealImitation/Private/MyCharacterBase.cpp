// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "MyComponent/MyDamageReceiver.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageReceiver = CreateDefaultSubobject<UMyDamageReceiver>(TEXT("DamageReceiver"));

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	if (DamageReceiver != nullptr)
	{
		DamageReceiver->OnDead.AddDynamic(this, &AMyCharacterBase::Dead);
		DamageReceiver->OnHealthChanged.AddDynamic(this, &AMyCharacterBase::PrintHealth);
	}
}

// Called every frame
void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ĳ���� �̵��ӵ� �����´�.
	MovingSpeed = GetVelocity().Size2D(); //FVector Length XY

}

// Called to bind functionality to input
void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacterBase::Dead()
{
	//ĳ���� �����Ʈ ����
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	//�ݸ��� ����.
	SetActorEnableCollision(false);

	//����ǰ��ִ� ��� �ִϸ��̼� ��Ÿ�� ����.
	StopAnimMontage();

}

void AMyCharacterBase::PrintHealth(float HealthPower, float MaxHealthPower)
{
	//ĳ������ �̸�
	FString CharacterName = GetName();

	UE_LOG(LogTemp, Display, TEXT("Max %s Health :%f\n\n"), *CharacterName, DamageReceiver->GetMaxHealthPower());
	UE_LOG(LogTemp, Display, TEXT("Current %s Health : %f\n\n"), *CharacterName, DamageReceiver->GetHealthPower());
}

float AMyCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//������ ������.
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageReceiver != nullptr)
	{
		DamageReceiver->OnDamageReceived(FinalDamage);
	}

	return FinalDamage;
}

void AMyCharacterBase::DashToTimeLine(float TimeLineValue,float DashSpeed)
{
	FVector DashLocation;
	float CurrentTimePrev = TimeLineValue - TimeLinePrev;

	CurrentTimePrev = CurrentTimePrev * DashSpeed;

	DashLocation = GetActorForwardVector() * CurrentTimePrev;

	AddActorWorldOffset(DashLocation, true);

	TimeLinePrev = TimeLineValue;
}

