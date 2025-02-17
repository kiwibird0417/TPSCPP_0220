// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"

#include "Enemy.h"

void UEnemyAnim::AnimNotify_AttackEnd()
{
	AEnemy* enemy = Cast<AEnemy>(TryGetPawnOwner());
	if( enemy != nullptr )
	{
		enemy->fsm->OnAttackEnd();
	}
}

void UEnemyAnim::AnimNotify_DieEnd()
{
	// 넘어지는 애니메이션이 끝남
	AEnemy* enemy = Cast<AEnemy>( TryGetPawnOwner() );
	if( enemy != nullptr )
	{
		enemy->fsm->OnDieEnd();
	}
}