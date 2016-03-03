// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Lever.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ALever : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TArray<AInteractable*> TargetToAffect;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		virtual void Interact(AActor* Interactor);

	UPROPERTY(EditAnywhere)
	bool bIsActivated;

	UFUNCTION()
	bool GetIsActivated();

	//Make it so this level can only be flipped once.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FlipOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* ActivationSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* DeactivationSound;

private:
	float activationTimer;

protected:

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
	//Check if this level has been flipped before.
	bool Flipped = false;

};
