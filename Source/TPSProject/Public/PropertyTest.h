// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropertyTest.generated.h"

UCLASS()
class TPSPROJECT_API APropertyTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropertyTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 들어가는 순서는 상관 없다!
	// 그치만 에디터에서 보일지 안 보일 지--> 블루프린트에서 사용할 것인가 --> 카테고리 이름 설정
	// 카테고리의 경우 대분류 소분류가 가능하다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ParentCategory | ChildCategory")
	int32 SampleVar = 0;

	//---------------------------------------------------------------------------------------
	// Edit						// Visible
	// EditDefaultsOnly			// VisibleDefaultsOnly
	// EditInstanceOnly			// VisibleInstanceOnly
	// EditAnywhere				// VisibleAnywhere

	// Visible => 값을 보기 가능, 수정 불가
	// Edit	   => 값을 수정 가능(보기 가능/default)
	
	// DefaultsOnly		=> 블루프린트 에디터 창의 디테일 패널
	// InstanceOnly		=> 월드 상에 배치된 오브젝트의 디테일 패널
	// Anywhere			=> 둘 다
	
	// Category 
	//---------------------------------------------------------------------------------------
	UPROPERTY()		//UPROPERTY() 디폴트 값은 어떨까?
	int32 Empty_Property = 0;

	UPROPERTY(EditDefaultsOnly, Category = "PropertyTest | Edit" )
	int32 Edit_DefaultsOnly = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PropertyTest | Edit" )
	int32 Edit_DO_BRO = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropertyTest | Edit" )
	int32 Edit_DO_BRW = 0;

	UPROPERTY(EditInstanceOnly, Category = "PropertyTest | Edit" )
	int32 Edit_InstanceOnly = 0;

	UPROPERTY(EditInstanceOnly , BlueprintReadOnly , Category = "PropertyTest | Edit" )
	int32 Edit_IO_BRO = 0;

	UPROPERTY(EditInstanceOnly , BlueprintReadWrite , Category = "PropertyTest | Edit" )
	int32 Edit_IO_BRW = 0;

	UPROPERTY(EditAnywhere, Category = "PropertyTest | Edit" )
	int32 Edit_Anywhere = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PropertyTest | Edit" )
	int32 Edit_Anywhere_BRO = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PropertyTest | Edit" )
	int32 Edit_Anywhere_BRW = 0;

	//-----------------------------------------------------------------------------
	//==============Visible============================================/
	UPROPERTY(VisibleDefaultsOnly, Category = "PropertyTest | Visible" )
	int32 Visible_DefaultsOnly = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PropertyTest | Visible" )
	int32 Visible_DO_BRO = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PropertyTest | Visible" )
	int32 Visible_DO_BRW = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "PropertyTest | Visible" )
	int32 Visible_InstanceOnly = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly , Category = "PropertyTest | Visible" )
	int32 Visible_IO_BRO = 0;

	UPROPERTY(VisibleInstanceOnly , BlueprintReadWrite , Category = "PropertyTest | Visible" )
	int32 Visible_IO_BRW = 0;

	UPROPERTY(VisibleAnywhere, Category = "PropertyTest | Visible" )
	int32 Visible_Anywhere = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "PropertyTest | Visible" )
	int32 Visible_Anywhere_BRO = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite , Category = "PropertyTest | Visible" )
	int32 Visible_Anywhere_BRW = 0;

	// 불르푸린트에서 해당 변수를 읽기만 가능.
	UPROPERTY(BlueprintReadOnly, Category = "PropertyTest | Blueprint")
	int32 Blueprint_ReadOnly = 0;
	
	// 블루프린트에서 해당 변수를 읽기와 쓰기 가능
	UPROPERTY(BlueprintReadWrite, Category = "PropertyTest | Blueprint")
	int32 Blueprint_ReadWrite = 0;



	//------------------------------------------------------------------------------------//
	/*/=================================[ UFUNCTION ]====================================/*/

	// BlueprintCallable => C++에서 작성한 함수를 블루프린트에서 사용할 수 있게 해준다.
	UFUNCTION(BlueprintCallable, Category = "FunctionTest")
	float GetValue_Callble_1(){return 10.0f;};

	UFUNCTION(BlueprintCallable, Category = "FunctionTest")
	float GetValue_Callable_2(float fValue){return fValue * 10.0f; };

	// BlueprintPure -> 특정 값 하나만 리턴받을 때 ==> 실행핀 없이, get value의 형태로 들고 온다.
	UFUNCTION(BlueprintPure, Category = "FunctionTest")
	float GetValue_Pure() {return 10.0f;};

	UFUNCTION(BlueprintPure, Category = "FunctionTest")
	float GetValue_Pure_2(float fValue) 
	{
		return fValue * 10.0f;
	};

	// 블루프린트에서 작성된 함수를, C++로 들고 오기
	// BlueprintImplementableEvent => C++에서 블루프린트 함수를 호출할 수 있게 해준다.
	// 1, C++에서 함수 원형을 작성하고
	UFUNCTION(BlueprintImplementableEvent, Category = "FunctionTest")
	void CallBlueprintFunc_1();

	UFUNCTION(BlueprintImplementableEvent, Category = "FunctionTest")
	void CallBlueprintFunc_2(float fValue);

	// 2. 블루 프린트에서 해당 함수의 기능을 작성하고
	// 3. C++에서 해당 함수를 호출해서 사용한다.




};
