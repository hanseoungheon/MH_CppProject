// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyCharacterState.h"
#include "MyPlayerHunter.generated.h"


UCLASS()
class MH_UNREALIMITATION_API AMyPlayerHunter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPSCAM, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPSCAM, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	// Sets default values for this character's properties
	AMyPlayerHunter();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void IsInteract_PickUpWeapon(bool Trigger, AActor* WeaponActor);


	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SpawnDummys();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnLongSwordAndHouse();

	UFUNCTION(BlueprintCallable, Category = "State")
	ECharacterState GetCharacterState() const;

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetState(const ECharacterState NewState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void BeginRun();

	void StopRun();

	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void PickUpTheWeapon(FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void StartPickUp();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Run;
	//UPROPERTY(EditAnywhere, Category = "Input")

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Attack;


public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyLongSword* LongSword = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyDummyWeapon* DummyLongSword = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon/LongSword")
	class AMyDummyLSHouse* DummyLSHouse = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHunterCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHasWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bIsHanging = true;





protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState State = ECharacterState::Peace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed = 300.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool IsBeRun = false;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim/LongSword")
	class UAnimMontage* DrawLongSword = nullptr;
	
	
};
