// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWeapon.h"
#include "MyLongSword.generated.h"

/**
 * 
 */

//�µ� ���η���.
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

	//�µ����� �ʿ��Ѱ�
	//���� ���� ��?
public:
	//�µ� ���η��� ����ġ�ϴ� �Լ�.
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
