// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TheSaveGame.generated.h"

/**
*
*/
UCLASS()
class FIRSTPERSONINPUT_API UTheSaveGame : public USaveGame
{
	GENERATED_BODY()

	UTheSaveGame();

public:
	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		float SavedFantasyCounter;

	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		FName LevelToLoad;

	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		FVector CheckPointAt;

	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		FName PlayerStart;

	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintEditable, Category = Basic)
		uint32 UserIndex;

};
