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

UCLASS()
class MH_UNREALIMITATION_API AMyLongSword : public AMyWeapon
{
	GENERATED_BODY()

	//태도에게 필요한것
	//기인 레벨 끝?
public:
	//태도 기인레벨 스위치하는 함수.
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SwitchLongSwordLevel();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	ELongSwordLevel KiinLevel = ELongSwordLevel::LSLevel0;

private:
	float longSwordBaseDamage = 50.0f;
};
