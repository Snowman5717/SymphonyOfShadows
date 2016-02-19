// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "PeterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API UPeterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStartedJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStartLanding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLanded = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteracting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;
	
	
};
