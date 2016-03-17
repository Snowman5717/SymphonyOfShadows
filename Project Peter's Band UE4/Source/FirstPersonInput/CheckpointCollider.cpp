// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "CheckpointCollider.h"


// Sets default values
ACheckpointCollider::ACheckpointCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetBoxExtent(FVector(200.f, 200.f, 100.f));

	RootComponent = Collider;

	OnActorBeginOverlap.AddDynamic(this, &ACheckpointCollider::OnActorOverlap);
	//OnActorEndOverlap.AddDynamic(this, &ACheckpointCollider::OnActorOverlapEnd);
}

// Called when the game starts or when spawned
void ACheckpointCollider::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckpointCollider::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ACheckpointCollider::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor); 
			if (Player)
			{
				Player->SavePlayerGame(SectionNumber, GetActorLocation());
			}
		}
	}
}

//void ACheckpointCollider::OnActorOverlapEnd(AActor* OtherActor)
//{
//	if (OtherActor != GetOwner())
//	{
//		if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
//		{
//			GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, OtherActor->GetName());
//		}
//	}
//}