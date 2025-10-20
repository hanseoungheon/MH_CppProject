// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyDamageReceiver.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, HealthPower, float, MaxHealthPower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged, float, NewDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MH_UNREALIMITATION_API UMyDamageReceiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyDamageReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void OnDamageReceived(float NewDamage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ReturnToVulnerable();

public:

	//Getter Setter

	float GetMaxHealthPower() const
	{
		return MaxHealthPower;
	}

	void SetMaxHealthPower(const float NewMaxHealthPower)
	{
		MaxHealthPower = NewMaxHealthPower;
	}

	float GetHealthPower() const
	{
		return HealthPower;
	}

	void SetHealthPower(const float NewHealthPower)
	{
		HealthPower = NewHealthPower;
	}

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDamaged OnDamaged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDead OnDead;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MaxHealthPower = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HealthPower = 0.0f;

	bool bVulnerable = true; //공격을 맞았을때 매 틱마다 계산되는걸 방지하기 위해서 잠깐의 무적시간을 부여할때 사용되는 불리언변수.
	float InVulnerableTime = 0.5f; //무적시간.

	FTimerHandle VulnerableTimerHandle;


		
};
