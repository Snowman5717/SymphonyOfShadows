// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "PeterAnimInstance.h"

void UPeterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ACharacter* CharacterOwner = Cast<ACharacter>(TryGetPawnOwner());

	if (CharacterOwner)
	{
		MoveSpeed = CharacterOwner->GetVelocity().Size();
	}
}


