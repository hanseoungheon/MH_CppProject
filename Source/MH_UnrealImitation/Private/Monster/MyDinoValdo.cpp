// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyDinoValdo.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyDinoValdo::AMyDinoValdo()
{
	WalkSpeed = 200.0f;
	RunSpeed = 600.0f;

	SpecialDashTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpecialDashTimeline"));
}

void AMyDinoValdo::BeginPlay()
{
	Super::BeginPlay();

	if (SpecialDashTimeline != nullptr)
	{
		FOnTimelineFloat SpecialDashInterpFunction;
		FOnTimelineEvent SpecialDashFinishedFunction;

		SpecialDashInterpFunction.BindUFunction(this, FName("DashToSpeicalDash"));
		SpecialDashTimeline->AddInterpFloat(SpecialDashCurve, SpecialDashInterpFunction);

		SpecialDashFinishedFunction.BindUFunction(this, FName("DashEndToTimeLine"));
		SpecialDashTimeline->SetTimelineFinishedFunc(SpecialDashFinishedFunction);

		SpecialDashTimeline->SetLooping(false);
		SpecialDashTimeline->SetPlayRate(1.0f);
	}
}

void AMyDinoValdo::Angry()
{
}

void AMyDinoValdo::DashToSpeicalDash(float TimeLineValue)
{
	float DashPower = 2000.0f;
	//UE_LOG(LogTemp, Display, TEXT("DINOVALDO SPD TEST"));
	DashToPlayerOfTimeLine(TimeLineValue, DashPower);
}
