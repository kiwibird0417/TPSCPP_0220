// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// 랜덤한 시간 구하기
	float createTime = FMath::RandRange(minTime, maxTime);
	// Timer Manager 한테 등록
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime );
	
	// 스폰위치 동적 할당
	FindSpawnPoints();	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	// 랜덤한 스폰위치 구하기
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);

	// 적을 배치하기
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0) );

	// 랜덤한 시간을 구하기
	float createTime = FMath::RandRange(minTime, maxTime);

	// 다시 타이머에 등록하기
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	//for( TActorIterator<AActor> it(GetWorld()); it; ++it )
	//{
	//	AActor* spawn = *it;
	//	// 찾은 해당 액터의 이름에서 해당 문자열을 포함하고 있다면
	//	if( spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint") ) )
	//	{
	//		// 스폰 목록에 추가
	//		spawnPoints.Add(spawn);
	//	}
	//}


	// 검색으로 찾은 결과를 저장할 배열
	TArray<AActor*> allActors;
	// 원하는 타입의 액터를 모두 찾아오기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	// 찾은 결과가 있을경우에는 반복적으로 처리
	for(auto spawn : allActors)
	{
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if( spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint") ) )
		{
			// 스폰 목록에 추가
			spawnPoints.Add( spawn );
		}
	}
}

