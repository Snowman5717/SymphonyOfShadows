#include "FirstPersonInput.h"
#include "SharkAI.generated.h"

UCLASS()
class ASharkAI : public AAIController
{
	GENERATED_UCLASS_BODY()

	

	UPROPERTY(transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	virtual void Possess(class APawn* InPawn) OVERRIDE;

	virtual void BeginInactiveState() OVERRIDE;

	void Respawn();

	 /* Defining enemy values.
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetEnemy(class APawn* InPawn);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	class AFirstPersonInput* GetEnemy() const;


	


	UFUNCTION(BlueprintCallable, Category = Behaviour)
	bool PawnCanBeSeen(APawn * target);

       /* Currently checking to see the nearest shark in relation to the player.
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void SearchEnemyInView();

       /* Getting enemy Key.
protected:
	int32 EnemyKeyID;		
};