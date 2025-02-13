// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY( EditDefaultsOnly , Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* tpsCamComp;

	// 총 스켈레탈 메시
	UPROPERTY( VisibleAnywhere, Category = GunMesh )
	class USkeletalMeshComponent* GunMeshComp;

	// 총알 공장
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> BulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction*	IA_Fire;

	// 총알 발사 처리함수
	void InputFire(const FInputActionValue& inputValue);


	// 스나이퍼건 스태틱메시 추가
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent*	SniperGunMesh;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_GrenadeGun;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_SniperGun;

	// 유탄총 사용중인지 여부
	bool bUsingGrenadeGun = true;

	// 유탄총으로 변경
	void ChangeToGrenadeGun(const FInputActionValue& inputValue);

	// 스나이퍼건으로 변경
	void ChangeToSniperGun( const FInputActionValue& inputValue );


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Sniper;

	// 스나이퍼 조준처리함수
	void SniperAim(const FInputActionValue& inputValue );

	// 스나이퍼 조준 중인지 여부
	bool bSniperAim = false;


	// 스나이퍼 UI 위젯 공장
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> SniperUIFactory;

	// 스나이퍼 UI 위젯 인스턴스
	UPROPERTY()
	class UUserWidget* SniperUI;


	// 총알 파편 효과 공장
	UPROPERTY( EditAnywhere, Category = BulletEffect )
	class UParticleSystem*	BulletEffectFactory;


	// 일반 조준 크로스헤어UI 위젯
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> CrossHairUIFactory;

	// 크로스헤어 인스턴스
	class UUserWidget* _CrossHairUI;




	// Input
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext*	IMC_TPS;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LookUp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;



	// 좌우 회전 입력 처리
	void Turn(const FInputActionValue& inputValue);

	// 상하 회전 입력 처리
	void LookUp(const FInputActionValue& inputValue);


	// 사용자의 좌우 입력을 받아서 이동하고 싶다.
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Move;

	// 이동 속도
	UPROPERTY( EditAnywhere, Category = PlayerSetting )
	float WalkSpeed = 200.0f;

	// 달리기 속도
	UPROPERTY( EditAnywhere, Category = PlayerSetting )
	float RunSpeed = 600.0f;

	// 이동 방향
	FVector Direction;

	void Move(const FInputActionValue& inputValue);

	// 점프
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Jump;

	void InputJump(const FInputActionValue& inputValue);


	// 달리기
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Run;

	void InputRun();


	// 쪼그려 걷기
	// LCtrl 버튼을 누르고 있으면 쪼그리기, 떼면 해제
	// C 버튼을 누르면 쪼그리기, 다시 누르면 해제
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_CrouchCtrl;
	void InputCrouchCtrl();
	void InputUnCrouchUnCtrl();

	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_CrouchC;
	void InputCrouchToggle();

	bool bCrouched = false;

	UPROPERTY()
	class UTPSPlayerAnimInstance* Anim;


	// 카메라 셰이크 블루프린트를 저장할 변수
	UPROPERTY(EditDefaultsOnly, Category = CameraMotion)
	TSubclassOf<class UCameraShakeBase> CameraShake;

	// 총알 발사 사운드
	UPROPERTY(EditDefaultsOnly, Category = Sound )
	class USoundBase* BulletSound;
};
