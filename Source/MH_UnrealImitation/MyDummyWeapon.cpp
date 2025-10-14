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

		switch (CharState)
		{
		case ECharacterState::Peace: 
			DummyWeaponMesh->SetVisibility(true); //���࿡ Peace �� ���������� ���¸� ���̰˵��� ��������.
			break;

		case ECharacterState::Battle:
			DummyWeaponMesh->SetVisibility(false); //���࿡ Battle �� �������� ���¸� ���̰˵��� ��������.
			break;

		case ECharacterState::Draw:
			DummyWeaponMesh->SetVisibility(false); //���࿡ Draw �� ���� �̰��ִ»��¸� ���̰��� ������ �ȵ�.
			break;

		case ECharacterState::Sheath:
			DummyWeaponMesh->SetVisibility(true); //���࿡ Sheath �� ���� �ְ��ִ� ���¸� ���̰��� ��������.
			break;

		default:
			break;
		}
	}
}

