// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyMoster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerHunter.h"
#include "Perception/PawnSensingComponent.h"
#include "Animation/AnimMontage.h"

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

void AMyMoster::Angry()
{
	//GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

