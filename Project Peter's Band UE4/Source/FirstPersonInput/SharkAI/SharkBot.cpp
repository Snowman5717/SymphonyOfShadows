// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonInput.h"
#include "SharkBot.generated.h"


ASharkBot::ASharkBot(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = ASharkAI::StaticClass();

	UpdatePawnMeshes();

	AttackRange = 100;
	AttackDamage = 10;	
	bUseControllerRotationYaw = true;
}


bool ASharkBot::IsFirstPerson() const
{
	return false;
}
void ASharkBot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}
