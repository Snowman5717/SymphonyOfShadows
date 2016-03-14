// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interactables/Interactable.h"
#include "Interactables/LightSwitch.h"
#include "Interactables/Lever.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "AnchovieCharacter.generated.h"


UCLASS()
class FIRSTPERSONINPUT_API AAnchovieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnchovieCharacter();

	void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh1;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh2;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh3;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh4;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh5;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh6;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh7;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh8;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh9;

	UPROPERTY(EditAnywhere)
		USoundCue* SplashSound;


	/*UPROPERTY(EditAnywhere)
		TArray<AActor*> Waypoints;*/

	UPROPERTY(EditAnywhere)
	bool LightOn;
	/*
	UPROPERTY(EditAnywhere)
	float WaypointAt;

	UPROPERTY(EditAnywhere)
	FName DestinationKeyName;

	UPROPERTY(EditAnywhere)
	FName NextDestination;

	UFUNCTION()
		void NextWayPoint();*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPathing")
		USplineComponent* PatrolPath;

	UPROPERTY()
		float DistanceOnSpline;

	UPROPERTY(EditAnywhere)
		float AnchovySpeed;

	FRotator rotationTarget;

protected:


	UFUNCTION()
		void OnActorOverlaping(AActor* OtherActor);

	UPROPERTY()
		ALever *LeverToCollideWith;

	UPROPERTY()
		ALightSwitch *TheSwitch;
};
