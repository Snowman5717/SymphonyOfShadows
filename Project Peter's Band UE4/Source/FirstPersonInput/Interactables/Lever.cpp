// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "InteractDoors.h"
#include "InteractableAnimInstance.h"
#include "Lever.h"


// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->AttachTo(SkeletalMesh);

	Collider->SetBoxExtent(FVector(50, 50, 10));
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALever::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALever::Interact(AActor* OtherActor)
{
	UInteractableAnimInstance* LeverAnimation = NULL;

	if (SkeletalMesh)
	{
		LeverAnimation = Cast<UInteractableAnimInstance>(SkeletalMesh->GetAnimInstance());
	}

	if (bIsActivated)
	{
		bIsActivated = false;
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Lever Deactivated");
		
		if (LeverAnimation)
		{
			LeverAnimation->bActivated = false;
		}

	}
	else
	{
		bIsActivated = true;
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Lever Activated");
		if (LeverAnimation)
		{
			LeverAnimation->bActivated = true;
		}
	}

	for (int i = 0; i < TargetToAffect.Num(); i++)
	{
		if (TargetToAffect[i] != nullptr)
		{
			if (TargetToAffect[i]->GetName().Contains("Door"))
			{
				Cast<AInteractDoors>(TargetToAffect[i])->SwitchInteract(OtherActor);
			}
			else
			{
				TargetToAffect[i]->Interact(OtherActor);
			}
		}
	}
}

bool ALever::GetIsActivated()
{
	return bIsActivated;
}

