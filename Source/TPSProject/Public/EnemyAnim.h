// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	EEnemyState AnimState;

	// 공격 상태 재생할지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	bool bAttackPlay = false;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = FSM )
	class UAnimMontage*	EnemyMontage;

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DieEnd();
	
};
