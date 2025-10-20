// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MyMoster.h"
#include "Components/TimelineComponent.h"
#include "MyDinoValdo.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API AMyDinoValdo : public AMyMoster
{
	GENERATED_BODY()
	
public:
	AMyDinoValdo();
protected:
	virtual void BeginPlay() override;

	virtual void Angry() override;

	UFUNCTION(Category = "Attack")
	void DashToSpeicalDash(float TimeLineValue);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UTimelineComponent* SpecialDashTimeline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	UCurveFloat* SpecialDashCurve = nullptr;



protected:

};
