// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "InteractableAnimInstance.h"
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

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->AttachTo(DoorHinge);

	//Collider->AttachTo(DoorHinge);

	RootComponent = DoorHinge;

}

// Called when the game starts or when spawned
void AInteractDoors::BeginPlay()
{
	Super::BeginPlay();

	bIsOpen = false;
	rotationClosed = GetActorRotation();
	rotationOpen = GetActorRotation();
	rotationOpen.Yaw += 90;
}

// Called every frame
void AInteractDoors::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bIsOpen)
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotationOpen, DeltaTime, 5.f));
	}
	else
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotationClosed, DeltaTime, 5.f));
	}
}

void AInteractDoors::Interact(AActor* Interactor)
{
		if (!bIsLocked)
		{
				if (bIsOpen)
				{
					bIsOpen = false;
				}
				else
				{
					bIsOpen = true;
				}
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundEffect, GetActorLocation());

				UInteractableAnimInstance* DoorAnim = Cast<UInteractableAnimInstance>(SkeletalMesh->GetAnimInstance());
				
				if (DoorAnim)
				{
					DoorAnim->bActivated = true;
				}
		}
}

void AInteractDoors::SwitchInteract(AActor* Interactor)
{
		if (bIsOpen)
		{
			bIsOpen = false;
		}
		else
		{
			bIsOpen = true;
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundEffect, GetActorLocation());
}