// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SetMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API USetMaxWalkSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UPROPERTY(EditAnywhere)
	float DesiredMaxSpeed = 0.f;
};
