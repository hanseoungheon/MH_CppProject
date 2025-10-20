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

	//시작시 무기의 에리도 최대치로 설정.
	sharpness = MaxSharpness;

	//구체 콜리전 생성 => 플레이어와의 상호작용에 쓰입니다.
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	RootComponent = SphereCollision;

	SphereCollision->InitSphereRadius(200.0f);

	SphereCollision->SetCollisionProfileName(TEXT("Trigger"));

	SphereCollision->SetGenerateOverlapEvents(true);

	SphereCollision->bHiddenInGame = true;

	//무기 메시 생성
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->SetupAttachment(SphereCollision);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	WeaponMesh->SetRelativeRotation(FRotator::ZeroRotator);
	WeaponMesh->SetRelativeScale3D(FVector(1.0f));

	WeaponMesh->SetSimulatePhysics(false);

	//공격 판정용 콜리전 생성
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
	//예리도 감소.
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
		//만약에 무기를 매고있으면 보이지 않게 무기를 들고 있다면 보이게.
		ECharacterState CharState = PlayerCharacter->GetCharacterState();

		//캐릭터 상태를 가져와서 상태별로 점검.
		switch (CharState)
		{
		case ECharacterState::Peace:
			WeaponMesh->SetVisibility(false); //만약 Peace 즉 납도상태면 검이 보이면 안됨.
			break;

		case ECharacterState::Battle:
			WeaponMesh->SetVisibility(true); //만약 Battle 즉 전투상태면 검이 보여야함.
			break;

		case ECharacterState::Draw:
			WeaponMesh->SetVisibility(true); //만약 Draw 즉 검을 뽑는중인 상태면 검이 보여야함.
			break;

		case ECharacterState::Sheath:
			WeaponMesh->SetVisibility(false); //만약 Sheath 즉 검을 넣는중인 상태면 검이 보이면 안됨.
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

	// Instigator를 못 받았으면, 무기 Instigator(소유자 Pawn)에서 가져오기
	if (InstigatorCtrl == nullptr)
	{
		InstigatorCtrl = GetInstigatorController();  // ← BeginPlay의 SetInstigator 덕분에 정확
	}

	AActor* DamageCauser = this; // 무기 자체가 공격 주체

	UGameplayStatics::ApplyDamage(
		Other,
		BaseDamage,
		InstigatorCtrl,
		DamageCauser,
		UDamageType::StaticClass()
	);
}

