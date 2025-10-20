// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWeapon.h"
#include "MyLongSword.generated.h"

/**
 * 
 */

//태도 기인레벨.
UENUM(BlueprintType)
enum class ELongSwordLevel : uint8
{
	LSLevel0 UMETA(DisPlayName = "LSLevel0"),
	LSLevel1 UMETA(DisPlayName = "LSLevel1"),
	LSLevel2 UMETA(DisPlayName = "LSLevel2"),
	LSLevel3 UMETA(DisPlayName = "LSLevel3"),
};

//태도 기인베기 동작이 몇단계인지
UENUM()
enum class EKiinAttackLevel : uint8
{
	KIINLevel1 UMETA(DisplayName = "KIINLevel1"),
	KIINLevel2 UMETA(DisplayName = "KIINLevel2"),
	KIINLevel3 UMETA(DisplayName = "KIINLevel3"),
	KIINLevel4 UMETA(DisplayName = "KIINLevel4"),
};

UCLASS()
class MH_UNREALIMITATION_API AMyLongSword : public AMyWeapon
{
	GENERATED_BODY()

	//태도에게 필요한것
	//기인 레벨 끝?
public:
	AMyLongSword();

	//태도 기인레벨 스위치하는 함수.
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SwitchLongSwordLevel();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void IsOverlapToSphere(AActor* OtherActor) override;

	virtual void IsEndOverlapToSphere(AActor* OtherActor) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	ELongSwordLevel KiinLevel = ELongSwordLevel::LSLevel0; //기인레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	EKiinAttackLevel KiinSkillLevel = EKiinAttackLevel::KIINLevel1; //기인베기의 단계레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	bool bIsIai;

	//간파베기 회피.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool Dodge_Ganpa = false;

	//특납 회피
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool Dodge_Iai = false;



private:
	float longSwordBaseDamage = 50.0f;


};
