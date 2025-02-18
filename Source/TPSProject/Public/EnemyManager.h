// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"


// 랜덤한 시간 ( 최소값, 최대값 )
// 스폰이 될 위치 목록
// 적공장

UCLASS()
class TPSPROJECT_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// 랜덤한 시간 최소값
	UPROPERTY( EditAnywhere, Category = SpawnSetting)
	float minTime = 1.0f;

	// 랜덤한 시간 최대값
	UPROPERTY( EditAnywhere, Category = SpawnSetting)
	float maxTime = 5.0f;

	// 스폰할 위치 정보 배열
	UPROPERTY( EditAnywhere , Category = SpawnSetting )
	TArray<class AActor*>	spawnPoints;

	// AEnemy 팩토리
	UPROPERTY( EditAnywhere, Category = SpawnSetting)
	TSubclassOf<class AEnemy> enemyFactory;

	// 스폰을 위한 타이머
	FTimerHandle	spawnTimerHandle;

	// 적 생성 하는 함수
	void CreateEnemy();

	// 스폰할 위치를 동적으로 찾아서 할당하기
	void FindSpawnPoints();

};
