// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Bullet.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyFSM.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh에 퀸을 로드해서 넣고싶다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/ Script / Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));

	// 만약 파일읽기가 성공했다면
	if( TempMesh.Succeeded() )
	{
		// 로드한 메시를 넣어주고 싶다.
		GetMesh()->SetSkeletalMesh(TempMesh.Object);

		// 위치값과 회전값을 반영해주고 싶다.
		GetMesh()->SetRelativeLocationAndRotation(FVector( 0.0f, 0.0f, -90.0f ), FRotator( 0.0f, -90.0f, 0.0f ) );
	}

	// TPS카메라를 붙이고 싶다.
	// SpringArm 컴포넌트 붙이기
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment( RootComponent );
	springArmComp->SetRelativeLocation( FVector( 0.0f, 60.0f, 80.0f ) );
	springArmComp->TargetArmLength = 300.0f;
	springArmComp->bUsePawnControlRotation = true;

	// Camera 컴포넌트 붙이기
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment( springArmComp );
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;


	// 총 스켈레탈 메시 컴포넌트 등록
	GunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT("GunMeshComp") );

	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	GunMeshComp->SetupAttachment( GetMesh() );

	// 스켈레탈 메시 데이터 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh( TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'") );

	// 데이터 로드가 성공했다면
	if( TempGunMesh.Succeeded() )
	{
		// 스켈레탈 메시 데이터 할당
		GunMeshComp->SetSkeletalMesh( TempGunMesh.Object );

		// 총 위치 설정
		GunMeshComp->SetRelativeLocation( FVector( 0.0f, 60.0f, 120.0f ) );
	}

	// 스나이퍼건 컴포넌트 등록
	SniperGunMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("SniperGunMesh") );

	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	SniperGunMesh->SetupAttachment( GetMesh() );

	// 스태틱 메시 데이터 로드
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempSniperMesh( TEXT("/Script/Engine.StaticMesh'/Game/SniperGun/sniper11.sniper11'") );

	// 데이터 로드가 성공했다면
	if( TempSniperMesh.Succeeded() )
	{
		// 스태틱 메시 데이터 할당
		SniperGunMesh->SetStaticMesh(TempSniperMesh.Object);

		// 총 위치 설정
		SniperGunMesh->SetRelativeLocation( FVector( 0.0f, 50.0f, 120.0f ) );

		// 총 크기 설정
		SniperGunMesh->SetRelativeScale3D( FVector( 0.15f ) );
	}



	
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if( pc )
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if( subsystem )
		{
			subsystem->AddMappingContext(IMC_TPS, 0);
		}
	}	

	//JumpMaxCount = 3;

	// 스나이퍼 UI 위젯 인스턴스 생성
	SniperUI = CreateWidget( GetWorld(), SniperUIFactory );

	// 일반 조준 UI 크로스헤어 인스턴스 생성
	_CrossHairUI = CreateWidget(GetWorld(), CrossHairUIFactory );

	// 일반 조준 UI 등록
	_CrossHairUI->AddToViewport();
	
	// 기본으로 스나이퍼건을 사용하도록 설정
	ChangeToSniperGun(FInputActionValue());
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P(결과위치) = P0(현재위치) + v(속도) x t(시간)	
	Direction = FTransform(GetControlRotation()).TransformVector(Direction);
	
	/*
	FVector P0 = GetActorLocation();
	FVector vt = Direction * WalkSpeed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation( P );
	*/
	AddMovementInput(Direction);

	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = Cast<UEnhancedInputComponent>( PlayerInputComponent );
	if( PlayerInput )
	{
		PlayerInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATPSPlayer::Turn);
		PlayerInput->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ATPSPlayer::LookUp);

		PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);

		PlayerInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &ATPSPlayer::InputJump);

		// 총알 발사 이벤트 처리 함수 바인딩
		PlayerInput->BindAction(IA_Fire, ETriggerEvent::Started, this, &ATPSPlayer::InputFire);

		// 총 교체 이벤트 처리함수 바인딩
		PlayerInput->BindAction(IA_GrenadeGun, ETriggerEvent::Started, this, &ATPSPlayer::ChangeToGrenadeGun);

		PlayerInput->BindAction( IA_SniperGun , ETriggerEvent::Started , this , &ATPSPlayer::ChangeToSniperGun );

		// 스나이퍼 조준모드 이벤트 처리 함수 바인딩
		PlayerInput->BindAction( IA_Sniper, ETriggerEvent::Started, this, &ATPSPlayer::SniperAim);
		PlayerInput->BindAction( IA_Sniper , ETriggerEvent::Completed, this , &ATPSPlayer::SniperAim );

	}
}

void ATPSPlayer::InputFire( const FInputActionValue& inputValue )
{
	// 유탄총 사용 시
	if( bUsingGrenadeGun == true )
	{
		// 총알 발사 처리
		FTransform firePosition = GunMeshComp->GetSocketTransform( TEXT("FirePosition") );

		GetWorld()->SpawnActor<ABullet>( BulletFactory, firePosition );
	}
	// 스나이퍼건 사용 시
	else
	{
		// LineTrace 의 시작위치
		FVector startPos = tpsCamComp->GetComponentLocation();

		// LineTrace 의 종료위치
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000.0f;
		
		// LineTrace 의 충돌 정보를 담을 변수
		FHitResult hitInfo;

		// 충돌 옵션 설정 변수
		FCollisionQueryParams params;

		// 자기 자신(플레이어)는 충돌에서 제외
		params.AddIgnoredActor(this);

		// Channel필터를 이용한 LineTrace 충돌 검출
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECollisionChannel::ECC_Visibility, params);

		// LineTrace가 충돌했을때
		if( bHit == true )
		{
			// 충돌 처리 -> 충돌효과 표현

			// 총알 파편 효과 트랜스폼
			FTransform BulletTrans;

			// 부딪힌 위치 할당
			BulletTrans.SetLocation( hitInfo.ImpactPoint );

			// 총알 파편 효과 인스턴스 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletEffectFactory, BulletTrans);

			auto hitComp = hitInfo.GetComponent();

			// 만약에 컴포넌트에 물리가 적용되어 있다면
			if( hitComp && hitComp->IsSimulatingPhysics() )
			{
				// 조준한 방향이 필요
				FVector dir = ( endPos - startPos ).GetSafeNormal();

				// 날려 버릴 힘 ( F = ma )
				FVector force = dir * hitComp->GetMass() * 500000;

				// 그 방향으로 날려 버리고 싶다.
				hitComp->AddForceAtLocation(force, hitInfo.ImpactPoint);
			}

			// 부딪힌 대상이 적인지 체크
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName( TEXT("FSM") );
			if( enemy )
			{
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				enemyFSM->OnDamageProcess();
			}
		}
	}
}

void ATPSPlayer::ChangeToGrenadeGun( const FInputActionValue& inputValue )
{
	// 유탄총 사용 중으로 체크
	bUsingGrenadeGun = true;
	SniperGunMesh->SetVisibility( false );
	GunMeshComp->SetVisibility( true );
}

void ATPSPlayer::ChangeToSniperGun( const FInputActionValue& inputValue )
{
	bUsingGrenadeGun = false;
	SniperGunMesh->SetVisibility( true );
	GunMeshComp->SetVisibility( false );
}

void ATPSPlayer::SniperAim( const FInputActionValue& inputValue )
{
	// 스나이퍼건 모드가 아니라면 처리하지 않는다.
	if( bUsingGrenadeGun )
	{
		return;
	}

	// Pressed 입력 처리
	if( bSniperAim == false )
	{
		// 스나이퍼 조준 모드 활성화
		bSniperAim = true;
		// 스나이퍼 조준 UI 등록
		SniperUI->AddToViewport();
		// 카메라의 시야각 FOV(Field Of View) 설정
		tpsCamComp->SetFieldOfView(45.0f);
		// 일반 조준 UI 제거
		_CrossHairUI->RemoveFromParent();
	}
	// Released 입력 처리
	else
	{
		// 스나이퍼 조준 모드 비활성화
		bSniperAim = false;
		// 스나이퍼 조준 UI 화면에서 제거
		SniperUI->RemoveFromParent();
		// 카메라 시야각을 원래대로 복원
		tpsCamComp->SetFieldOfView(90.0f);
		// 일반 조준 UI 등록
		_CrossHairUI->AddToViewport();
	}
}

void ATPSPlayer::Turn( const FInputActionValue& inputValue )
{
	float value = inputValue.Get<float>();
	AddControllerYawInput(value);
}

void ATPSPlayer::LookUp( const FInputActionValue& inputValue )
{
	float value = inputValue.Get<float>();
	AddControllerPitchInput(value);
}

void ATPSPlayer::Move( const FInputActionValue& inputValue )
{
	FVector2D value = inputValue.Get<FVector2D>();

	// 상하 입력 처리
	Direction.X = value.X;

	// 좌우 입력 처리
	Direction.Y = value.Y;
}

void ATPSPlayer::InputJump( const FInputActionValue& inputValue )
{
	Jump();
}

