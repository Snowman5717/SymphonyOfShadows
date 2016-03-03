// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "InteractDoors.h"


// Sets default values
AInteractDoors::AInteractDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	DoorHinge = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Hinge"));
	DoorHinge->SetBoxExtent(FVector(5, 10, 5));
	DoorHinge->AddLocalOffset(FVector(-50, 0, 0));

	//Collider->AttachTo(DoorHinge);

	RootComponent = DoorHinge;

}

// Called when the game starts or when spawned
void AInteractDoors::BeginPlay()
{
	Super::BeginPlay();

	bIsOpen = false;
	rotationTarget = GetActorRotation();
}

// Called every frame
void AInteractDoors::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeBeforeOpening += DeltaTime;

	if (bIsOpen)
	{

			if (bOneTime)
			{
				rotationTarget = GetActorRotation();
				rotationTarget.Yaw += 90;
				bOneTime = false;
			}

			SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotationTarget, DeltaTime, 10.f));

	}
	else
	{

			if (bOneTime)
			{
				rotationTarget = GetActorRotation();
				rotationTarget.Yaw -= 90;
				bOneTime = false;
			}
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotationTarget, DeltaTime, 10.f));

	}
}

void AInteractDoors::Interact(AActor* Interactor)
{
		if (!bIsLocked)
		{
			if (timeBeforeOpening > 0.8)
			{
				if (bIsOpen)
				{
					bOneTime = true;
					bIsOpen = false;
				}
				else
				{
					bOneTime = true;
					bIsOpen = true;
				}
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundEffect, GetActorLocation());
				timeBeforeOpening = 0;
			}
		}
}

void AInteractDoors::SwitchInteract(AActor* Interactor)
{
	if (timeBeforeOpening > 0.8)
	{
		if (bIsOpen)
		{
			bOneTime = true;
			bIsOpen = false;
		}
		else
		{
			bOneTime = true;
			bIsOpen = true;
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundEffect, GetActorLocation());
		timeBeforeOpening = 0;
	}
}