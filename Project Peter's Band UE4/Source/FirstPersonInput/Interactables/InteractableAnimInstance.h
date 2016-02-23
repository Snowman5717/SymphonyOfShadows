// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "InteractableAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API UInteractableAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActivated;
	
};
