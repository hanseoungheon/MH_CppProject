// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void IsOverlaptoSphere(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void IsEndOverlaptoSphere(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* WeaponMesh;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	float baseDamage = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
	float sharpness;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
	float MaxSharpness = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	class AMyPlayerHunter* PlayerCharacter;
	


};
