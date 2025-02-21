// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Kismet/KismetMathLibrary.h"
#include "Turtle.h"


// Sets default values
ATurtle::ATurtle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StatMesh;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();

	bVisible = true;

	if (MoveRelativeTo != NULL)
	{
		RelativeLocation = GetActorLocation() - MoveRelativeTo->GetActorLocation();
		RelativeRotation = GetActorRotation();
	}
}

// Called every frame
void ATurtle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
	if (StatMesh->IsSimulatingPhysics())
	{
		StatMesh->SetPhysicsAngularVelocity(FVector(0, 0, SpinSpeed), false);
	}

	if (MoveRelativeTo != NULL)
	{
		FVector RotatedPosition = MoveRelativeTo->GetActorRotation().RotateVector(RelativeLocation);
		SetActorLocation(RotatedPosition + MoveRelativeTo->GetActorLocation());
		SetActorRotation(MoveRelativeTo->GetActorRotation() + RelativeRotation);
	}
}

void ATurtle::EnemyInteract(AActor* Interactor)
{
	//DO INTERACTIONS HERE
	if (StatMesh->IsSimulatingPhysics())
	{
		StatMesh->SetSimulatePhysics(false);
	}
	else if (!StatMesh->IsSimulatingPhysics())
	{
		StatMesh->SetSimulatePhysics(true);
	}
}

void ATurtle::PowerOff()
{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
}

void ATurtle::PowerOn()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
