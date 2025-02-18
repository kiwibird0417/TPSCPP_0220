// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UPlayerMoveComponent : public UActorComponent
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

	void SetupInputBinding(class UEnhancedInputComponent* input);
		
public:
	// 컴포넌트 소유 액터
	UPROPERTY()
	ATPSPlayer*	me;

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
};
