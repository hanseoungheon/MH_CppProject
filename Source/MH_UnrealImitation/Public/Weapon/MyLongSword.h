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

//�µ� ���κ��� ������ ��ܰ�����
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

	//�µ����� �ʿ��Ѱ�
	//���� ���� ��?
public:
	AMyLongSword();

	//�µ� ���η��� ����ġ�ϴ� �Լ�.
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SwitchLongSwordLevel();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void IsOverlapToSphere(AActor* OtherActor) override;

	virtual void IsEndOverlapToSphere(AActor* OtherActor) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	ELongSwordLevel KiinLevel = ELongSwordLevel::LSLevel0; //���η���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	EKiinAttackLevel KiinSkillLevel = EKiinAttackLevel::KIINLevel1; //���κ����� �ܰ跹��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	bool bIsIai;

	//���ĺ��� ȸ��.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool Dodge_Ganpa = false;

	//Ư�� ȸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool Dodge_Iai = false;



private:
	float longSwordBaseDamage = 50.0f;


};
