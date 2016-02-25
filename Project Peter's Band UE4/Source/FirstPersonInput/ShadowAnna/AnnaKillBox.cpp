// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "AnnaKillBox.h"


// Sets default values
AAnnaKillBox::AAnnaKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	OnActorBeginOverlap.AddDynamic(this, &AAnnaKillBox::OnActorOverlap);

}

void AAnnaKillBox::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor == Cast<APlayerCharacter>(OtherActor) || OtherActor == Cast<AShadowAnnaCharacter>(OtherActor))
		{
			if (ShadowAnna)
			{
				ShadowAnna->Destroy();
			}
		}
	}
}