// Fill out your copyright notice in the Description page of Project Settings.


#include "MyComponent/MyDamageReceiver.h"
#include "TimerManager.h"
// Sets default values for this component's properties

UMyDamageReceiver::UMyDamageReceiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UMyDamageReceiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	HealthPower = MaxHealthPower;
}


// Called every frame
void UMyDamageReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyDamageReceiver::OnDamageReceived(float NewDamage)
{
	UE_LOG(LogTemp, Display, TEXT("공격이 실행되는지 테스트입니다."));
	if (bVulnerable == true)
	{
		bVulnerable = false;

		UWorld* world = GetWorld();

		if (world == nullptr)
		{
			return;
		}

		world->GetTimerManager().SetTimer(
			VulnerableTimerHandle,
			this,
			&UMyDamageReceiver::ReturnToVulnerable,
			InVulnerableTime,
			false
		);

		HealthPower -= NewDamage;

		if (HealthPower <= 0)
		{
			HealthPower = 0;

			OnDead.Broadcast();
			OnHealthChanged.Broadcast(HealthPower, MaxHealthPower);
		}
		else
		{
			OnHealthChanged.Broadcast(HealthPower, MaxHealthPower);
		}

	}
}

void UMyDamageReceiver::ReturnToVulnerable()
{
	bVulnerable = true;
}

