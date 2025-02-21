// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "AnnaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API UAnnaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

		virtual void NativeUpdateAnimation(float DeltaTime) override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayFlairOne;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayFlairTwo;

protected:

	UPROPERTY(BlueprintReadWrite)
	uint8 IdleCount;

	UFUNCTION(BlueprintCallable, Category = "RandomFunction")
	uint8 RandomNumber();




	
	
};
