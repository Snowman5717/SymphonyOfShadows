// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TheSaveGame.h"



UTheSaveGame::UTheSaveGame()
{


}

void UTheSaveGame::ResetData()
{
	SavedFantasyCounter = 0;
	LevelToLoad = "SectionZero";
	CheckPointAt = FVector(-220.0f, 340.0f, 102.0f);
	PlayerStart = "PlayerStart";
}

void UTheSaveGame::SaveData(FName loadingLevel, FVector cp)
{
	LevelToLoad = loadingLevel;
	CheckPointAt = cp;
}

FName UTheSaveGame::ReturnLevelToLoad()
{

	return LevelToLoad;

}
FVector UTheSaveGame::ReturnCheckPoint()
{

	return CheckPointAt;

}

bool UTheSaveGame::GetIsStarting()
{
	return StartingGame;
}

void UTheSaveGame::SetIsStarting(bool starting)
{
	StartingGame = starting;
}