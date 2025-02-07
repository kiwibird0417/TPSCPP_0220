// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh에 퀸을 로드해서 넣고싶다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh( TEXT( "/ Script / Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'" ) );

	// 만약 파일읽기가 성공했다면
	if( TempMesh.Succeeded() )
	{
		// 로드한 메시를 넣어주고 싶다.
		GetMesh()->SetSkeletalMesh( TempMesh.Object );

		// 위치값과 회전값을 반영해주고 싶다.
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0.0f , 0.0f , -90.0f ) , FRotator( 0.0f , -90.0f , 0.0f ) );
	}

	// EnemyFSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>( TEXT("FSM") );

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

