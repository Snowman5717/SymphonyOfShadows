// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnchovieCharacter.h"
//#include "AnchovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"

// Sets default values
AAnchovieCharacter::AAnchovieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	AIControllerClass = AAnchovieController::StaticClass();

	//WaypointAt = 0;
	LightOn = false;

	AnchovySpeed = 333;

	skeleMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh1"));
	skeleMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh2"));
	skeleMesh3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh3"));
	skeleMesh4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh4"));
	skeleMesh5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh5"));
	skeleMesh6 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh6"));
	skeleMesh7 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh7"));
	skeleMesh8 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh8"));
	skeleMesh9 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh9"));

	skeleMesh1->AttachTo(RootComponent);
	skeleMesh2->AttachTo(RootComponent);
	skeleMesh3->AttachTo(RootComponent);
	skeleMesh4->AttachTo(RootComponent);
	skeleMesh5->AttachTo(RootComponent);
	skeleMesh6->AttachTo(RootComponent);
	skeleMesh7->AttachTo(RootComponent);
	skeleMesh8->AttachTo(RootComponent);
	skeleMesh9->AttachTo(RootComponent);
	/*
	AAnchovieController* Controller;
	Controller = Cast<AAnchovieController>(this->GetController());*/

	OnActorBeginOverlap.AddDynamic(this, &AAnchovieCharacter::OnActorOverlaping);

}

void AAnchovieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PatrolPath != NULL)
	{
		if (LightOn == true)
		
		{
			if (PatrolPath->GetSplineLength() <= DistanceOnSpline)
			{
				DistanceOnSpline = 0;
			}
			else
			{
				DistanceOnSpline += AnchovySpeed * DeltaTime;
			}
			SetActorRotation(PatrolPath->GetRotationAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World));
			SetActorLocation(PatrolPath->GetLocationAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World));
		}
		else
		{
			if (DistanceOnSpline <= 0)
			{
				DistanceOnSpline = PatrolPath->GetSplineLength();
			}
			else
			{
				DistanceOnSpline -= AnchovySpeed * DeltaTime;
			}
			rotationTarget = PatrolPath->GetRotationAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World);
			rotationTarget.Yaw += 180;
			SetActorRotation(rotationTarget);
			SetActorLocation(PatrolPath->GetLocationAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World));
		}
	}


}

void AAnchovieCharacter::OnActorOverlaping(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetName().Contains("Lever"))
		{
			LeverToCollideWith = Cast<ALever>(OtherActor);

			if (LeverToCollideWith != NULL)
			{
				if (LeverToCollideWith->GetIsActivated() == true)
				{
					LeverToCollideWith->Interact(this);
				}
			}
		}
		else if (OtherActor->GetName().Contains("Light"))
		{
			TheSwitch = Cast<ALightSwitch>(OtherActor);

			if (TheSwitch != NULL)
			{
				if (TheSwitch->GetIsOn() == true)
				{
					if (LightOn == false)
					{
						LightOn = true;
					}
					else
					{
						LightOn = false;
					}
				}
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SplashSound, GetActorLocation());
			}
		}
	}
}
/*
void AAnchovieCharacter::NextWayPoint()
{

	AAnchovieController* Controller;

	Controller = Cast<AAnchovieController>(this->GetController());
	if (Waypoints.Num() > 1)
	{
		if (!LightOn)
		{
			if (Waypoints.Last() == Waypoints[WaypointAt])
			{
				WaypointAt = 0;
			}
			else
			{
				WaypointAt += 1;
			} 
		}
		else
		{
			if (WaypointAt == 0)
			{
				WaypointAt = (Waypoints.Num() - 1);
			}
			else
			{
				WaypointAt -= 1;
			}
		}
		if (Controller != nullptr)
		{
			Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(DestinationKeyName, Waypoints[WaypointAt]->GetActorLocation());
			if (Waypoints.Num() == WaypointAt + 1)
			{
				Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(NextDestination, Waypoints[0]->GetActorLocation());
			}
			else
			{
				Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(NextDestination, Waypoints[WaypointAt + 1]->GetActorLocation());
			}
		}
	}
}*/