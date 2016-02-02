// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AnchovieController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API AAnchovieController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAnchovieController();
	virtual void Possess(APawn* Pawn) override;
	
	UBlackboardComponent* GetBlackBoardComponent();
	
	UFUNCTION()
		void RedirectToCharacter(AActor* OtherActor);

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComponent;

};

