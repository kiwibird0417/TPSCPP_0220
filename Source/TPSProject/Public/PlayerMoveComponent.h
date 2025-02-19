// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UPlayerMoveComponent : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInputBinding(class UEnhancedInputComponent* input) override;
		
public:
	UPROPERTY()
	UCharacterMovementComponent*	MoveComp;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LookUp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;

	// 좌우 회전 입력 처리
	void Turn( const FInputActionValue& inputValue );

	// 상하 회전 입력 처리
	void LookUp( const FInputActionValue& inputValue );


	// 사용자의 좌우 입력을 받아서 이동하고 싶다.
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Move;

	// 이동 방향
	FVector Direction;

	void Move( const FInputActionValue& inputValue );


	
	// 이동 속도
	UPROPERTY( EditAnywhere, Category = PlayerSetting )
	float WalkSpeed = 200.0f;

	// 달리기 속도
	UPROPERTY( EditAnywhere, Category = PlayerSetting )
	float RunSpeed = 600.0f;


	// 달리기
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Run;

	void InputRun();


	// 점프
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	class UInputAction* IA_Jump;

	void InputJump(const FInputActionValue& inputValue);

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


};
