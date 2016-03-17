// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Interactables/Interactable.h"
#include "Interactables/LiftableBox.h"
#include "Interactables/LightSwitch.h"
#include "Animations/PeterAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "ChoiceCheck.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.f);

	BaseTurnRate = 60.f;
	BaseLookUpRate = 60.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;


	//BOX PICKUP CODE//
	Hand = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	Hand->AttachTo(FirstPersonCameraComponent);
	Hand->RelativeLocation = FVector(100, 0, 0);
	//BOX PICKUP CODE//

	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlapEnd);

	PhysicsHandler = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandler"));

}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	bCurrentlyLiftingBox = false;

	FantasyCounter = SaveGameInstance->SavedFantasyCounter;
	UpdateCamera(FantasyCounter);

}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Z Velocity: %f"), GetVelocity().Z));

	if (isWalkingForward || isWalkingRight)
	{
		if (CanJump())
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), WalkSound, GetActorLocation());
	}
	if (isJumpingGruntCheck)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GruntSound, GetActorLocation());
		isJumpingGruntCheck = false;
	}

	if (GetVelocity().Z == 0 && isJumpingGroundCheck)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSound, GetActorLocation());
		isJumpingGroundCheck = false;

		UPeterAnimInstance* PeterAnimInstance = Cast<UPeterAnimInstance>(GetMesh()->GetAnimInstance());

		if (PeterAnimInstance)
		{
		}

		//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, TEXT("BOOP"));
	}
	if (CameraIsChanging == true)
	{
		UpdateCamera(FantasyCounter);
	}
	if (ShowTime == true)
	{
		FadeToWhite();
	}

	if (PhysicsHandleActive)
	{
		if (PhysicsHandler)
		{
			FVector HandleLocation;

			FVector ControllerForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());

			HandleLocation = ControllerForwardVector * 250 + GetActorLocation();

			HandleLocation.Z += 50;

			PhysicsHandler->SetTargetLocationAndRotation(HandleLocation, GetControlRotation());
		}
	}
	else if (PhysicsHandleActive == false)
	{
		PhysicsHandler->ReleaseComponent();
		if (PickedUpBox)
		{
			PickedUpBox->Drop(this);
		}
	}

	UPeterAnimInstance* PeterAnimInstance = Cast<UPeterAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("UseButton", IE_Pressed, this, &APlayerCharacter::ActivateButton);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Depending on the key pressed, will change the player's equip.
	InputComponent->BindAction("EquipSlot1", IE_Pressed, this, &APlayerCharacter::EquipSlot1);
	InputComponent->BindAction("EquipSlot2", IE_Pressed, this, &APlayerCharacter::EquipSlot2);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}
void APlayerCharacter::StartJump()
{
	if (GetVelocity().Z == 0)
	{
		isJumpingGruntCheck = true;
		isJumpingGroundCheck = true;

		UPeterAnimInstance* PeterAnimInstance = Cast<UPeterAnimInstance>(GetMesh()->GetAnimInstance());

		if (PeterAnimInstance)
		{
			PeterAnimInstance->bStartedJump = true;
		}

		Jump();
	}
}


//MOVEMENT CODE//
void APlayerCharacter::MoveForward(float Value)
{

	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		isWalkingForward = true;
	}
	else
		isWalkingForward = false;

}

void APlayerCharacter::MoveRight(float Value)
{

	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
		isWalkingRight = true;
	}
	else
		isWalkingRight = false;

}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); //yaw = horizontal rotation

}

void APlayerCharacter::LookUpAtRate(float Rate)
{

	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); //pitch vertical rotation

}
//MOVEMENT CODE END//


//USE BUTTON CODE//
void APlayerCharacter::ActivateButton()
{

	UPeterAnimInstance* PeterAnimInstance = Cast<UPeterAnimInstance>(GetMesh()->GetAnimInstance());

	if (PeterAnimInstance)
	{
		PeterAnimInstance->bIsInteracting = true;
	}

	if (PhysicsHandleActive)
	{
		PhysicsHandleActive = false;
	}
	else if (!PhysicsHandleActive)
	{
		PhysicsHandleActive = true;
	}

	bool TraceSuccess;

	FHitResult OutHit;

	//Uses Trace Channel: PlayerTrace 
	TraceSuccess = this->TraceFromSelf(OutHit, 300.f, ECollisionChannel::ECC_GameTraceChannel6);

	if (TraceSuccess)
	{
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, OutHit.GetActor()->GetName());

		AInteractable* InteractableObject = NULL;

		InteractableObject = Cast<AInteractable>(OutHit.GetActor());

		if (Cast<ALiftableBox>(OutHit.GetActor()))
		{
			if (PhysicsHandleActive)
			{
				PickedUpBox = Cast<ALiftableBox>(OutHit.GetActor());

				if (PickedUpBox->bIsAbove(this) && PickedUpBox->CanBeLifted == true)
				{
					PhysicsHandler->GrabComponent(OutHit.GetComponent(), OutHit.BoneName, OutHit.Location, true);
				}
			}
			return;
		}
		else if (InteractableObject && InteractableObject->GetClass()->IsChildOf(ALightSwitch::StaticClass()) == false)
		{
			if (FVector::Dist(GetActorLocation(), InteractableObject->GetActorLocation()) < 250)
			{
				InteractableObject->Interact(this);
			}
		}
	}
}
//USE BUTTON CODE END//


USceneComponent* APlayerCharacter::GetHand()
{
	//Returns the hand object that the mop and liftable objects attach to
	return Hand;
}


void APlayerCharacter::EquipSlot1() //Nothing Equipped
{
	EquippedIndex = 1;
	Unequip();
}
void APlayerCharacter::EquipSlot2() //First Equip
{
	if (UnlockedEquips >= 1)
	{
		EquippedIndex = 2;
		Equip(Equips[0]);
	}
}


void APlayerCharacter::Equip(TSubclassOf<ABaseEquips> EquipType)
{
	if (Equipped != NULL)
	{
		Unequip();
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	Equipped = GetWorld()->SpawnActor<ABaseEquips>(EquipType, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	Equipped->AttachRootComponentTo(GetMesh(), "BN_RPalm_01");
}

void APlayerCharacter::Unequip()
{
	if (Equipped != NULL)
	{
		Equipped->Destroy();
		Equipped = NULL;
	}
}

//Sets the players currently lifted object
void APlayerCharacter::SetObjectLifted(ALiftableBox* Box)
{
	PickedUpBox = Box;
	bCurrentlyLiftingBox = true;
}

void APlayerCharacter::SetLastChoice(bool ChoiceMade)
{
	LastChoiceMade = ChoiceMade;
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Black, TEXT("DING"));
}

bool APlayerCharacter::GetLastChoice()
{
	//true = reality
	//false = fantasy
	return LastChoiceMade;
}

void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetClass()->IsChildOf(AChoiceCheck::StaticClass()))
		{
			if (Cast<AChoiceCheck>(OtherActor)->IsReality())
			{
				FantasyCounter--;
				SaveGameInstance->SavedFantasyCounter = FantasyCounter;
				CameraIsChanging = true;
				SetLastChoice(true);
				OtherActor->Destroy();
			}
			else
			{
				FantasyCounter++;
				SaveGameInstance->SavedFantasyCounter = FantasyCounter;
				CameraIsChanging = true;
				SetLastChoice(false);
				OtherActor->Destroy();
			}
		}
		if (OtherActor->GetName().Contains("Dance"))
		{
			BeginTheShow = Cast<ATheatreSequence>(OtherActor);

			if (BeginTheShow != NULL)
			{
			WhereBeAnna = BeginTheShow->GetAnnasPos();
				ShowTime = true;
			}

		}
		if (OtherActor->ActorHasTag("End"))
		{
			SaveGameInstance->endGame = true;
		}
	}
}

void APlayerCharacter::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//
	}
}

void APlayerCharacter::UpdateCamera(float Counter)
{
	if (Counter == 0)
	{
		GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation = 1;
		GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity = 0;
	}
	else if (Counter == 1)
	{
		if (GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation < 1.2)
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation += 0.005;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity += 0.0025;
		}
		else
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation = 1.2;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity = 0.1;
			CameraIsChanging = false;
		}
	}
	else if (Counter == 2)
	{
		if (GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation < 1.4)
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation += 0.005;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity += 0.0025;
		}
		else
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation = 1.4;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity = 0.2;
			CameraIsChanging = false;
		}
	}
	else if (Counter > 2)
	{
		if (GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation < 1.6)
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation += 0.005;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity += 0.0025;
		}
		else
		{
			GetFirstPersonCameraComponent()->PostProcessSettings.FilmSaturation = 1.6;
			GetFirstPersonCameraComponent()->PostProcessSettings.VignetteIntensity = 0.3;
			CameraIsChanging = false;
		}
	}
}

void APlayerCharacter::FadeToWhite()
{

	DistanceToX = GetDistanceTo(WhereBeAnna);
	if (DistanceToX > 50)
	{
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorOffset.X = 20 / DistanceToX;
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorOffset.Y = 20/ DistanceToX;
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorOffset.Z = 20 / DistanceToX;
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorContrast.X = 1 - 20 / DistanceToX;
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorContrast.Y = 1 - 20 / DistanceToX;
		GetFirstPersonCameraComponent()->PostProcessSettings.ColorContrast.Z = 1 - 20 / DistanceToX;
	}
	else
	{
		ShowTime = false;
	}
}

bool APlayerCharacter::TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel)
{
	FVector PlayerLocation = this->GetActorLocation();

	//GetPlayerViewPoint is used to give the origin and direction
	//of the trace from the player

	FVector const StartTrace = PlayerLocation;
	FVector const TraceDirection = this->GetActorForwardVector();
	FVector const EndTrace = StartTrace + TraceDirection*TraceDistance;

	//Struct that defines parameters into collision function
	FCollisionQueryParams TraceParams(FName(TEXT("TraceFromSelf")), true, this);

	bool bHitReturned = false;
	UWorld* const World = GetWorld();

	if (World)
	{
		bHitReturned = World->LineTraceSingleByChannel(OutResult, StartTrace, EndTrace, CollisionChannel, TraceParams);
	}
	return bHitReturned;
}

APlayerController* APlayerCharacter::GetPlayerController()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		return PlayerController;
	}

	else return NULL;
}

void APlayerCharacter::SavePlayerGame(FName section, FVector location)
{
	SaveGameInstance->SaveData(section, location, GetActorRotation());
	sectionName = section;
}

FName APlayerCharacter::GetSection()
{
	return sectionName;
}