// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDummyWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyPlayerHunter.h"
// Sets default values
AMyDummyWeapon::AMyDummyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� ���� �޽� ����
	DummyWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummyMesh"));
	RootComponent = DummyWeaponMesh;
	DummyWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DummyWeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	DummyWeaponMesh->SetRelativeRotation(FRotator::ZeroRotator);
	DummyWeaponMesh->SetRelativeScale3D(FVector(1.0f));

	DummyWeaponMesh->SetSimulatePhysics(false);

}

// Called when the game starts or when spawned
void AMyDummyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyDummyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyDummyWeapon::MySetOwner(AActor* NewOwner)
{
	SetOwner(NewOwner);
}

void AMyDummyWeapon::SetVisibleDummy()
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(GetOwner());

	if (PlayerCharacter != nullptr && PlayerCharacter->bHasWeapon)
	{
		ECharacterState CharState = PlayerCharacter->GetCharacterState();

		if (CharState == ECharacterState::Peace) //���� �������¸� Į���� ���� ���� ��������.
		{
			DummyWeaponMesh->SetVisibility(true);
		}
		else if (CharState == ECharacterState::Battle) //���� �ߵ����¸� Į���� ���� ���� ������ �ȵ�.
		{
			DummyWeaponMesh->SetVisibility(false);
		}
	}
}

