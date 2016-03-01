// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnnaDance_AudioTimer.h"


// Sets default values
AAnnaDance_AudioTimer::AAnnaDance_AudioTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnnaDance_AudioTimer::BeginPlay()
{
	Super::BeginPlay();

	DanceMusicTimer = DanceMusic->GetDuration();

	StartTimer();
	
}

// Called every frame
void AAnnaDance_AudioTimer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAnnaDance_AudioTimer::CountDownTimer()
{
	--DanceMusicTimer;

	if (DanceMusicTimer <= 0)
	{
		//When the timer is empty clear the timer so it doesnt count into the negatives, and then run the audio finished function
		GetWorldTimerManager().ClearTimer(DanceMusicTimerHandle);
		AudioFinished();
	}
}

void AAnnaDance_AudioTimer::StartTimer()
{
	//Function that handles ticking down as the voice over is playing. This makes the voice over "Unskippable"
	//Takes in the Time handler, the object, a function that in this case lowers the Voice over timer value, counts down by one second and tells it to keep repeating until 0
	GetWorldTimerManager().SetTimer(DanceMusicTimerHandle, this, &AAnnaDance_AudioTimer::CountDownTimer, 1.0f, true);

	//GameplayStatics function that plays a sound at the location of the light so we can properly use audio falloff.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DanceMusic, GetActorLocation());

}

void AAnnaDance_AudioTimer::AudioFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), "SectionOne");
}

