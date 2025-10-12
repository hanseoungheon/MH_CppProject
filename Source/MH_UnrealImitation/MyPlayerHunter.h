// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void BeginRun();

	void StopRun();
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHunterCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bHasWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bIsHanging = true;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed = 300.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool IsBeRun = false;

	
};
