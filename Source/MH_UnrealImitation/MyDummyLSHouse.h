// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyDummyWeapon.h"
#include "MyDummyLSHouse.generated.h"

/**
 * 
 */
UCLASS()
class MH_UNREALIMITATION_API AMyDummyLSHouse : public AMyDummyWeapon
{
	GENERATED_BODY()
	
public:
	virtual void SetVisibleDummy() override;
	
	//���ϱ� �����ε��� �Լ��� UFUNCTION�� �ο��� �� ���� �׷��� �̷��Թۿ� ����� ���µ���.
	UFUNCTION(BlueprintCallable, Category = "LongSword")
	void SetVisibleLSHouse();
};
