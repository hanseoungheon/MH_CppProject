// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/MyPlayerHunter.h"
#include "Kismet/GameplayStatics.h"
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

	//���� ������ �ݸ��� ����
	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision->SetupAttachment(SphereCollision);

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetInstigator(Cast<APawn>(GetOwner()));
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
		switch (CharState)
		{
		case ECharacterState::Peace:
			WeaponMesh->SetVisibility(false); //���� Peace �� �������¸� ���� ���̸� �ȵ�.
			break;

		case ECharacterState::Battle:
			WeaponMesh->SetVisibility(true); //���� Battle �� �������¸� ���� ��������.
			break;

		case ECharacterState::Draw:
			WeaponMesh->SetVisibility(true); //���� Draw �� ���� �̴����� ���¸� ���� ��������.
			break;

		case ECharacterState::Sheath:
			WeaponMesh->SetVisibility(false); //���� Sheath �� ���� �ִ����� ���¸� ���� ���̸� �ȵ�.
			break;

		default:
			break;
		}
	}
}

void AMyWeapon::OnAttackToBegin()
{
	UE_LOG(LogTemp, Display, TEXT("WP AttackBegin"));
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyWeapon::OnAttackToEnd()
{
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyWeapon::ApplyDamamge(AActor* Other, float BaseDamage, AController* InstigatorCtrl)
{
	if (Other == nullptr || Other == this)
	{
		return;
	}

	// Instigator�� �� �޾�����, ���� Instigator(������ Pawn)���� ��������
	if (InstigatorCtrl == nullptr)
	{
		InstigatorCtrl = GetInstigatorController();  // �� BeginPlay�� SetInstigator ���п� ��Ȯ
	}

	AActor* DamageCauser = this; // ���� ��ü�� ���� ��ü

	UGameplayStatics::ApplyDamage(
		Other,
		BaseDamage,
		InstigatorCtrl,
		DamageCauser,
		UDamageType::StaticClass()
	);
}

