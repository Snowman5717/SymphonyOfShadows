// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TheatreSequence.h"


// Sets default values
ATheatreSequence::ATheatreSequence()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AActor* ATheatreSequence::GetAnnasPos()
{
	if (AnnasPos != NULL)
	{
		return AnnasPos;
		Destroy();
	}
	else
	{
		return NULL;
		Destroy();
	}
}
