// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnnaAnimInstance.h"


void UAnnaAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ACharacter* CharacterOwner = Cast<ACharacter>(TryGetPawnOwner());

	if (CharacterOwner)
	{
		MoveSpeed = CharacterOwner->GetVelocity().Size();
	}
}

uint8 UAnnaAnimInstance::RandomNumber()
{
	return FMath::RandRange(1, 2);
}

