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
	UPROPERTY(VisibleAnywhere, Category = Basic)
		float SavedFantasyCounter;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FName LevelToLoad;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FVector CheckPointAt;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FName PlayerStart;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UFUNCTION(BlueprintCallable, Category = "SaveStuff")
		void ResetData();

	UFUNCTION(BlueprintCallable, Category = "SaveStuff")
		void SaveData(FName loadingLevel, FVector cp);

	UFUNCTION(BlueprintCallable, Category = "SaveStuff")
		FName ReturnLevelToLoad();

	UFUNCTION(BlueprintCallable, Category = "SaveStuff")
		FVector ReturnCheckPoint();
			
};
