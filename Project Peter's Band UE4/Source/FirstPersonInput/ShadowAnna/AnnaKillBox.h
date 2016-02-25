// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ShadowAnnaCharacter.h"
#include "AnnaKillBox.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AAnnaKillBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnnaKillBox();

	UPROPERTY(EditAnywhere)
	AShadowAnnaCharacter* ShadowAnna;

protected:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;

	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);
	
	
};
