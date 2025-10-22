// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework\Character.h"
#include "GameFramework\CharacterMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	MovingThreshold = 3.0f;
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());

	if (Character != nullptr)
	{
		//ĳ���� �����Ʈ ��������.
		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovement != nullptr)
	{
		//�ӵ� ���ϱ�.
		MyVelocity = CharacterMovement->Velocity;

		// == ������ Vector to xy
		MoveSpeed = MyVelocity.Size2D();

		bIsIdle = MoveSpeed < MovingThreshold;
	}
}
