// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"
#include "TPSPlayer.h"

// Sets default values for this component's properties
UPlayerBaseComponent::UPlayerBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
	// ...
}


void UPlayerBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<ATPSPlayer>(GetOwner());

	me->InputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);//오브젝트 등록

	//me->InputBindingDelegate.AddUFunction(this, TEXT("SetupInputBinding"));				//(==)함수 등록
	//me->InputBindingDelegate.AddLambda([this]()->void{});	//람다 등록(참고용)
	//[this]()->void{}
	// [캡처](매개변수)->반환 자료형{ 함수 본체 }
	// dynamic 쓸 때는 꼭 UFUNCTION() 붙여줘서 쓰자~~



}

// Called when the game starts
void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerBaseComponent::SetupInputBinding( class UEnhancedInputComponent* input )
{

}

