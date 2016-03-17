// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerHUD.h"
#include "NarrativeCollider.h"


// Sets default values
ANarrativeCollider::ANarrativeCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	OnActorBeginOverlap.AddDynamic(this, &ANarrativeCollider::OnActorOverlap);

}

// Called when the game starts or when spawned
void ANarrativeCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANarrativeCollider::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("HIT"));
		if (NarrativeSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), NarrativeSound, GetActorLocation());
		}

		if (!Subtitles.IsEmpty())
		{

			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("There are Words"));

			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (PlayerCharacter)
			{

				GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Found the Player"));

				APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerCharacter->GetPlayerController()->GetHUD());

				if (PlayerHUD)
				{

					GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Found the HUD"));

					PlayerHUD->SetSubtitles(Subtitles, Duration);

				}
			}
		}
	}

	Destroy();
}

