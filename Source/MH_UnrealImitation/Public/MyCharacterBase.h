// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacterBase.generated.h"

UCLASS()
class MH_UNREALIMITATION_API AMyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//죽는 함수.
	virtual void Dead();

	//캐릭터의 체력 출력
	void PrintHealth(float HealthPower, float MaxHealthPower);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void DashToTimeLine(float TimeLineValue,float DashSpeed);


protected:

//-----------------------------------------------------------------------------------------------------
public://클래스들 모아놓은 것.

protected: 
	//데미지 리시버.(캐릭터들이 공통으로 가지는 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	class UMyDamageReceiver* DamageReceiver = nullptr;


//-----------------------------------------------------------------------------------------------------
public: //변수들 모아놓은 섹션

protected:
	float WalkSpeed = 0.0f; //걷기 스피드.
	float RunSpeed = 0.0f; //뛰기 스피드.

	float MovingSpeed = 0.0f; //현재 걷는 속도.

		
	float TimeLinePrev = 0.0f; //타임라인 타이머용 변수.
	
//-----------------------------------------------------------------------------------------------------
//Getter & Setter 
public:
	//걷기/달리기 스피드부분은. 세터는 필요없을듯 단독으로는 더미값이라서.
	FORCEINLINE float GetCharacterWalkSpeed() const
	{
		return WalkSpeed;
	}

	FORCEINLINE float GetCharacterRunSpeed() const
	{
		return RunSpeed;
	}
};
