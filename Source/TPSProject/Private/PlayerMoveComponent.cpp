// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoveComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UPlayerMoveComponent::UPlayerMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//me = Cast<ATPSPlayer>(GetOwner());
	
}


// Called every frame
void UPlayerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerMoveComponent::SetupInputBinding( class UEnhancedInputComponent* input )
{
	input->BindAction( IA_Turn , ETriggerEvent::Triggered , this , &UPlayerMoveComponent::Turn );
	input->BindAction( IA_LookUp , ETriggerEvent::Triggered , this , &UPlayerMoveComponent::LookUp );
}



void UPlayerMoveComponent::Turn( const FInputActionValue& inputValue )
{
	float value = inputValue.Get<float>();
	me->AddControllerYawInput( value );
}

void UPlayerMoveComponent::LookUp( const FInputActionValue& inputValue )
{
	float value = inputValue.Get<float>();
	me->AddControllerPitchInput( value );
}

