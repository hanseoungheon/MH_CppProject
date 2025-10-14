// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyPlayerHunter.h"
// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���۽� ������ ������ �ִ�ġ�� ����.
	sharpness = MaxSharpness;

	//��ü �ݸ��� ���� => �÷��̾���� ��ȣ�ۿ뿡 ���Դϴ�.
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	RootComponent = SphereCollision;

	SphereCollision->InitSphereRadius(200.0f);

	SphereCollision->SetCollisionProfileName(TEXT("Trigger"));

	SphereCollision->SetGenerateOverlapEvents(true);

	SphereCollision->bHiddenInGame = true;

	//���� �޽� ����
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->SetupAttachment(SphereCollision);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	WeaponMesh->SetRelativeRotation(FRotator::ZeroRotator);
	WeaponMesh->SetRelativeScale3D(FVector(1.0f));

	WeaponMesh->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMyWeapon::DisCountSharpness(float DisSharp)
{
	//������ ����.
	sharpness -= DisSharp;
}

void AMyWeapon::IsOverlapToSphere(AActor* OtherActor)
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->bHunterCanInteract = true;
	}

}

void AMyWeapon::IsEndOverlapToSphere(AActor* OtherActor)
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->bHunterCanInteract = false;
	}
}

// Called every frame
void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyWeapon::SetVisibleWeapon()
{
	AMyPlayerHunter* PlayerCharacter = Cast<AMyPlayerHunter>(GetOwner());

	if (PlayerCharacter != nullptr && PlayerCharacter->bHasWeapon)
	{
		//���࿡ ���⸦ �Ű������� ������ �ʰ� ���⸦ ��� �ִٸ� ���̰�.
		ECharacterState CharState = PlayerCharacter->GetCharacterState();

		//ĳ���� ���¸� �����ͼ� ���º��� ����.
		if (CharState == ECharacterState::Peace) //���� Peace �� �������¸� ���� ���̸� �ȵ�.
		{
			WeaponMesh->SetVisibility(false);
		}
		else if (CharState == ECharacterState::Battle) //���� Battle �� �ߵ����¸� ���� ��������.
		{
			WeaponMesh->SetVisibility(true);
		}
	}
}

