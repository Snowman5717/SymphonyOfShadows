// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Equips/BaseEquips.h"
#include "TheSaveGame.h"
#include "Interactables/LiftableBox.h"
#include "Interactables/TheatreSequence.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	//FUNCTIONS

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	USceneComponent* GetHand();

	//A function that will equip an object of type ABaseEquips.
	void Equip(TSubclassOf<ABaseEquips> EquipType);
	void Unequip();

	//Depending on the key pressed, will change the player's equip.
	void EquipSlot1();
	void EquipSlot2();

	//Gives the player a reference to the lifted object (Used for dropping the box)
	void SetObjectLifted(ALiftableBox* Box);

	//Getter and Setter for the choice narrative options in the branching path system
	bool GetLastChoice();
	void SetLastChoice(bool ChoiceMade);

	UFUNCTION()
	void FadeToWhite();

	UFUNCTION()
	APlayerController* GetPlayerController();

	UFUNCTION()
	void SavePlayerGame(FName section, FVector location);

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	//FUNCTIONS

	UFUNCTION()
		void UpdateCamera(float Counter);

	void StartJump();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	//A function that handles the activate button press
	UFUNCTION()
	void ActivateButton();

	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);

	UFUNCTION()
	virtual void OnActorOverlapEnd(AActor* OtherActor);

	bool TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel);

private: 
	//FUNCTIONS

public:
	//VARIABLES

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	//Player specific sounds, set in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* GruntSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* JumpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* WalkSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveStuff")
	UTheSaveGame* SaveGameInstance;

	UPROPERTY()
	AActor* WhereBeAnna;

	UPROPERTY()
	float DistanceToX;

	UPROPERTY()
		ATheatreSequence *BeginTheShow;

protected:
	//VARIABLES

	UPROPERTY()
	ACameraActor* TheCameraToEffect;


	UPROPERTY()
	float FantasyCounter;

	bool ShowTime;

	bool CameraIsChanging;


	//Checks for what the player character is currently doing for sounds
	bool isWalkingForward;

	bool isWalkingRight;

	bool isJumpingGruntCheck;

	bool isJumpingGroundCheck;

	//Connection for Box and other liftable objects, curretly where the mop is being attached but
	//Mop will be moved to the models hand when it comes in.
	UPROPERTY(EditAnywhere)
	USceneComponent* Hand;

	//A list of the equips the player has available to them.
	//and an equipped variable to hold the currently equipped tool.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< TSubclassOf<ABaseEquips> > Equips;

	//A value that determines which equips the player has access to.
	//If 0, the player cannot equip anything, if 1, the player can
	//access the first element in the Equips array.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 UnlockedEquips;

	uint8 EquippedIndex;
	ABaseEquips* Equipped;


	UPROPERTY(VisibleDefaultsOnly, Category = PhysicHandle)
	UPhysicsHandleComponent* PhysicsHandler;

	bool PhysicsHandleActive;


private:
	//VARIABLES
	
	//Reference to the object that was picked up
	ALiftableBox *PickedUpBox;

	//Tells the player if they are currently lifting a box
	bool bCurrentlyLiftingBox;

	bool LastChoiceMade;

	//Needs to be moved to a ULocalPlayer class
	int32 ChoiceScale;
};