// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AnnaDance_AudioTimer.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AAnnaDance_AudioTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnnaDance_AudioTimer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	USoundCue* DanceMusic;

	//An int to hold the length of the sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DanceMusicTimer;

private:
	//A handler for the timer that is linked to the length of the sound
	FTimerHandle DanceMusicTimerHandle;

	//A function taht holds actions to take every time the timer ticks
	void CountDownTimer();

	//What to do when the audio finishes playing
	void AudioFinished();

	//What to do before and when the timer starts
	void StartTimer();

	
	
};
