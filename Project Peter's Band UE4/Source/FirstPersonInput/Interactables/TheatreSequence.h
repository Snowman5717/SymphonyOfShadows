// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheatreSequence.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ATheatreSequence : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATheatreSequence();


	UPROPERTY(EditAnywhere)
		AActor* AnnasPos;

	UFUNCTION()
		AActor* GetAnnasPos();

};
