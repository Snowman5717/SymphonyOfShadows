
#pragma once

#include "FirstPersonInput.h"
#include "SharkBot.generated.h"

UCLASS()
class ASharkBot : public AFirstPersonInput
{
	GENERATED_UCLASS_BODY()


	UPROPERTY(EditDefaultsOnly, Category = Behaviour)
	float AttackRange;
	UPROPERTY(EditDefaultsOnly, Category = Behaviour)
	float AttackDamage;
	
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void PerformMeleeAttack();

	float AccumulatedFiretime;

	virtual bool IsFirstPerson() const OVERRIDE;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) OVERRIDE;
	bool Attacking;
};