// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TheSaveGame.h"



UTheSaveGame::UTheSaveGame()
{
	SavedFantasyCounter = 0;
	LevelToLoad = "SectionZero";
	CheckPointAt = FVector (-220.0f, 340.0f, 102.0f);
	PlayerStart = "PlayerStart";
}