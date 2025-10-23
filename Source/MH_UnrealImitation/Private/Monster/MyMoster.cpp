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
AMyMonster::AMyMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(41.2f, 96.0f);


	TimeLinePrev = 0.0f;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing")); //폰센싱 생성
	PawnSensing->SensingInterval = 0.5f; 
	PawnSensing->bSeePawns = true; //볼수는 있음
	PawnSensing->bHearNoises = false; //근데 들을 수 는 없음
	PawnSensing->SetPeripheralVisionAngle(30.0f); //시야각
	PawnSensing->SightRadius = 2000.f; // 시야범위

	PawnSensing->OnSeePawn.AddDynamic(this, &AMyMonster::OnSeePawn);

	//키 설정.
	TargetPlayerKey = TEXT("TargetPlayer");
	StateKey = TEXT("State");
}

// Called when the game starts or when spawned
void AMyMonster::BeginPlay()
{
	Super::BeginPlay();

}

void AMyMonster::DashToPlayerOfTimeLine(float TimeLineValue, float DashSpeed)
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

void AMyMonster::DashEndToTimeLine()
{
	TimeLinePrev = 0.0f;
}

void AMyMonster::OnSeePawn(APawn* Pawn)
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
void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void AMyMonster::Dead()
{
	Super::Dead();
	State = EMonsterState::Dead;
}

void AMyMonster::ApplyDamamge(AActor* Other, float BaseDamage,AController* InstigatorCtrl)
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


void AMyMonster::Angry()
{
	//GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyMonster::SetMonsterState(const EMonsterState NewState)
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

