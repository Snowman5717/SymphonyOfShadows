// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* HUDFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TextPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor TextColor;

	void SetSubtitles(FString Subs, float Duration);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Subtitles;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
	
};
