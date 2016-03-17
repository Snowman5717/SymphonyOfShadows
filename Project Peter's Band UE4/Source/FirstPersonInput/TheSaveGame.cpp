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
	endGame = false;
}

void UTheSaveGame::SaveData(FName loadingLevel, FVector cp, FRotator rotation)
{
	LevelToLoad = loadingLevel;
	CheckPointAt = cp;
	pRotation = rotation;
}

FName UTheSaveGame::ReturnLevelToLoad()
{

	return LevelToLoad;

}
FVector UTheSaveGame::ReturnCheckPoint()
{

	return CheckPointAt;

}

FRotator UTheSaveGame::ReturnRotation()
{

	return pRotation;

}

bool UTheSaveGame::GetIsStarting()
{
	return StartingGame;
}

void UTheSaveGame::SetIsStarting(bool starting)
{
	StartingGame = starting;
}

float UTheSaveGame::ReturnFantasyCounter()
{
	return SavedFantasyCounter;
}

bool UTheSaveGame::IsGameEnded()
{
	return endGame;
}

void UTheSaveGame::SetGameEnded(bool endOrNah)
{
	endGame = endOrNah;
}