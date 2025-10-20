// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyMoster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerHunter.h"
#include "Perception/PawnSensingComponent.h"
#include "Animation/AnimMontage.h"
#include "MyComponent/MyDamageReceiver.h"
#include "AIController.h"

// Sets default values
AMyMoster::AMyMoster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(41.2f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TimeLinePrev = 0.0f;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing")); //폰센싱 생성
	PawnSensing->SensingInterval = 0.5f; 
	PawnSensing->bSeePawns = true; //볼수는 있음
	PawnSensing->bHearNoises = false; //근데 들을 수 는 없음
	PawnSensing->SetPeripheralVisionAngle(45.0f); //시야각
	PawnSensing->SightRadius = 2000.f; // 시야범위

	PawnSensing->OnSeePawn.AddDynamic(this, &AMyMoster::OnSeePawn);

	//키 설정.
	TargetPlayerKey = TEXT("TargetPlayer");
	StateKey = TEXT("State");
}

// Called when the game starts or when spawned
void AMyMoster::BeginPlay()
{
	Super::BeginPlay();

	DamageReceiver = FindComponentByClass<UMyDamageReceiver>(); //에디터에서 추가할거임.

	if (DamageReceiver != nullptr)
	{
		DamageReceiver->OnDead.AddDynamic(this, &AMyMoster::MonsterDead);
		DamageReceiver->OnHealthChanged.AddDynamic(this, &AMyMoster::PrintHelath);
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyMoster::DashToFrontOfTimeLine(float TimeLineValue, float DashSpeed)
{
	FVector DashLocation;

	float CurrentTimePrev = TimeLineValue - TimeLinePrev;

	CurrentTimePrev = CurrentTimePrev * DashSpeed;

	DashLocation = GetActorForwardVector() * CurrentTimePrev;

	AddActorWorldOffset(DashLocation, true);

	TimeLinePrev = TimeLineValue;
}

void AMyMoster::DashToPlayerOfTimeLine(float TimeLineValue, float DashSpeed)
{
	//UE_LOG(LogTemp, Display, TEXT("DINOVALDO SPD TEST"));
	AMyPlayerHunter* Hunter = Cast<AMyPlayerHunter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Hunter == nullptr)
	{
		return;
	}

	FVector DashLocation;

	float CurrentTimePrev = TimeLineValue - TimeLinePrev;

	CurrentTimePrev = CurrentTimePrev * DashSpeed;

	FVector PlayerLocation = (Hunter->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	DashLocation = PlayerLocation * CurrentTimePrev;

	AddActorWorldOffset(DashLocation, true);

	TimeLinePrev = TimeLineValue;
}

void AMyMoster::DashEndToTimeLine()
{
	TimeLinePrev = 0.0f;
}

void AMyMoster::OnSeePawn(APawn* Pawn)
{
	if (State == EMonsterState::Peace)
	{
		AMyPlayerHunter* Hunter = Cast<AMyPlayerHunter>(Pawn);

		if (Hunter->GetCharacterState() == ECharacterState::Dead)
		{
			return;
		}
		AMyMonsterAIController* MyAIController = Cast<AMyMonsterAIController>(GetController());

		if (MyAIController != nullptr)
		{
			UBlackboardComponent* BB = MyAIController->GetBlackboardComponent();

			if (BB == nullptr)
			{
				return;
			}

			PreState = State;

			SetMonsterState(EMonsterState::Roar);

			BB->SetValueAsObject(TargetPlayerKey, Hunter);

			PlayAnimMontage(RoarMontage, 1.0f, TEXT("Roar"));

			GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		}
	}
}
// Called every frame
void AMyMoster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyMoster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyMoster::PrintHelath(float HealthPower, float MaxHealthPower)
{
	UE_LOG(LogTemp, Display, TEXT("Max Monster Health :%f\n\n"),DamageReceiver->GetMaxHealthPower());
	UE_LOG(LogTemp, Display, TEXT("Current Monster Health : %f\n\n"), DamageReceiver->GetHealthPower());
}

float AMyMoster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageReceiver->OnDamageReceived(FinalDamage);

	return FinalDamage;
}

void AMyMoster::ApplyDamamge(AActor* Other, float BaseDamage,AController* InstigatorCtrl)
{
	if (Other == nullptr || Other == this)
	{
		return;
	}

	if (InstigatorCtrl == nullptr)
	{
		if (APawn* Pawn = Cast<APawn>(this))
		{
			InstigatorCtrl = Pawn->GetController(); // nullptr이어도 ApplyDamage는 호출 가능
		}
	}

	// 몬스터 본체가 때리므로 DamageCauser는 this
	AActor* DamageCauser = this;

	UGameplayStatics::ApplyDamage(
		Other,
		BaseDamage,
		InstigatorCtrl,
		DamageCauser,
		UDamageType::StaticClass()
	);
}


void AMyMoster::Angry()
{
	//GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyMoster::SetMonsterState(const EMonsterState NewState)
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

		BB->SetValueAsEnum(StateKey, static_cast<uint8>(NewState));
	}
}

