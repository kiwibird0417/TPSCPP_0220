// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnimInstance.h"
#include "TPSPlayer.h"

void UTPSPlayerAnimInstance::NativeUpdateAnimation( float DeltaSeconds )
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ATPSPlayer* player = Cast<ATPSPlayer>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}

	FVector velocity = player->GetVelocity();
	FVector forwardVector = player->GetActorForwardVector();

	// 앞 / 뒤 이동속도
	Speed = FVector::DotProduct(forwardVector, velocity);
}
