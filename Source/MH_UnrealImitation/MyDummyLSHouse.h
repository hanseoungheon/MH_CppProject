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
	
	//보니깐 오버로드한 함수는 UFUNCTION을 부여할 수 없음 그래서 이렇게밖에 방법이 없는듯해.
	UFUNCTION(BlueprintCallable, Category = "LongSword")
	void SetVisibleLSHouse();
};
