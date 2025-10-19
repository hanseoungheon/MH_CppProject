// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyMoster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerHunter.h"

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
}

// Called when the game starts or when spawned
void AMyMoster::BeginPlay()
{
	Super::BeginPlay();
	
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

}

