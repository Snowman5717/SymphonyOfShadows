// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "LiftableBox.h"


// Sets default values
ALiftableBox::ALiftableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleBox"));

	RootComponent = VisibleBox;
}

// Called when the game starts or when spawned
void ALiftableBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALiftableBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ALiftableBox::Interact(AActor* Interactor)
{
}

void ALiftableBox::Drop(AActor* Player)
{
	VisibleBox->WakeRigidBody();

	VisibleBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	VisibleBox->SetRenderCustomDepth(false);
}

bool ALiftableBox::bIsAbove(AActor* Player)
{
	FVector PlayerToBox = Cast<APlayerCharacter>(Player)->GetActorLocation() - this->GetActorLocation();

	PlayerToBox.Normalize();

	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("Normalized Z Vector : %f"), PlayerToBox.Z));

	if (PlayerToBox.Z < 0.60f)
	{
		return true;
	}
	else
		return false;
}




