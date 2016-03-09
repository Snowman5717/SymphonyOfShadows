// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ShadowAnna/Animation/AnnaAnimInstance.h"
#include "SetMaxWalkSpeed.h"


EBTNodeResult::Type USetMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	AActor* AnnaActor = OwnerComp.GetBlackboardComponent()->GetOwner();

	if (AnnaActor)
	{
		ACharacter*  AnnaCharacter = Cast<AController>(AnnaActor)->GetCharacter();

		if (AnnaCharacter)
		{
			AnnaCharacter->GetCharacterMovement()->MaxWalkSpeed = DesiredMaxSpeed;

			EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}



