// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.h"
#include "TPSPlayer.h"
#include "PlayerFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UPlayerFireComponent : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInputBinding( class UEnhancedInputComponent* input ) override;
		
public:	
	UPROPERTY()
	class UCameraComponent*	tpsCamComp;

	UPROPERTY()
	class USkeletalMeshComponent*	GunMeshComp;

	UPROPERTY()
	class UStaticMeshComponent*		SniperGunMesh;



	// 총알 공장
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> BulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction*	IA_Fire;

	// 총알 발사 처리함수
	void InputFire(const FInputActionValue& inputValue);



	
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

	
	// 카메라 셰이크 블루프린트를 저장할 변수
	UPROPERTY(EditDefaultsOnly, Category = CameraMotion)
	TSubclassOf<class UCameraShakeBase> CameraShake;

	// 총알 발사 사운드
	UPROPERTY(EditDefaultsOnly, Category = Sound )
	class USoundBase* BulletSound;


};
