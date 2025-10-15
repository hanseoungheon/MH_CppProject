// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MyCharacterState.h"
#include "GameFramework/Actor.h"
#include "MyDummyWeapon.generated.h"

UCLASS()
class MH_UNREALIMITATION_API AMyDummyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDummyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* DummyWeaponMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void MySetOwner(AActor* NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void SetVisibleDummy();

	//UFUNCTION(BlueprintCallable, Category = "LongSword")
	//void SetVisibleLongSwordHouse();

};
