#include "FirstPersonShooter.h"



ASharkAI::ASharkAI(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
// create blackboard and behaviour components in the constructor
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;
}



void ASharkAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ASharkBot* Bot = Cast<ASharkBot>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior)
	{		

		BlackboardComp->InitializeBlackboard(Bot->BotBehavior->BlackboardAsset);

                // Get the enemy blackboard ID, and store it to access that blackboard key later.
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		

		BehaviorComp->StartTree(Bot->BotBehavior);
	}
}

void ASharkAI::BeginInactiveState()
{
	Super::BeginInactiveState();

	AGameState* GameState = GetWorld()->GameState;

	const float MinRespawnDelay = (GameState && GameState->GameModeClass) ? GetDefault<AGameMode>(GameState->GameModeClass)->MinRespawnDelay : 1.0f;

	GetWorldTimerManager().SetTimer(this, &ASharkAI::Respawn, MinRespawnDelay);
}

void ASharkAI::Respawn()
{
//	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}




void ASharkAI::SetEnemy(class APawn* InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
		SetFocus(InPawn);
	}
}

class AFirstPersonShooter* ASharkAI::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<AFirstPersonShooter>(BlackboardComp->GetValueAsObject(EnemyKeyID));
	}

	return NULL;
}


void ASharkAI::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector FocalPoint = GetFocalPoint();
	if (!FocalPoint.IsZero() && GetPawn())
	{
		FVector Direction = FocalPoint - GetPawn()->GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();

		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);

		SetControlRotation(NewControlRotation);

		APawn* const P = GetPawn();
		if (P && bUpdatePawn)
		{
			P->FaceRotation(NewControlRotation, DeltaTime);
		}

	}
}


bool ASharkAI::PawnCanBeSeen(APawn * target)
{
	if (target == NULL || GetPawn() == NULL)
	{
		return false;
	}
	FVector difference = target->GetActorLocation() - GetPawn()->GetActorLocation();
	float angle = FVector::DotProduct(difference, GetPawn()->GetActorRotation().Vector());

	if (LineOfSightTo(target, GetPawn()->GetActorLocation()) && angle >0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void ASharkAI::SearchEnemyInView()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AFirstPersonShooter* BestPawn = NULL;

	//foreach all pawns in world
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		UE_LOG(LogShooterWeapon, Log, TEXT(" ENEMY SEEN %s "), *GetNameSafe(*It));
		if (PawnCanBeSeen(*It))
		{
			AFirstPersonShooter* TestPawn = Cast<AFirstPersonShooter>(*It);

			if (TestPawn && TestPawn->IsAlive() && Cast<ASharkBot>(TestPawn) == NULL)
			{
				const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
 				if (DistSq < BestDistSq)
				{
					 BestDistSq = DistSq;
					BestPawn = TestPawn;
				 }
 			}
		}
	}

	if (BestPawn)
	{
		// We saw someone, so set him as target.
		SetEnemy(BestPawn);
	
	}
	
}