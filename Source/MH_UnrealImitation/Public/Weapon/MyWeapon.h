// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MyCharacterState.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class MH_UNREALIMITATION_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//에리도 감소.
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void DisCountSharpness(float DisSharp = 2.0f);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void IsOverlapToSphere(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void IsEndOverlapToSphere(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Set Visibility Weapon Maybe Need Public
	//무기 보이게 할지 아니게 할지 트리거하는 함수. 
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetVisibleWeapon();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnAttackToBegin();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnAttackToEnd();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamamge(AActor* Other, float BaseDamage, AController* InstigatorCtrl);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	class UBoxComponent* AttackCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* WeaponMesh;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	float baseDamage = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
	float sharpness;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
	float MaxSharpness = 100.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	//class AMyPlayerHunter* PlayerCharacter;
};
