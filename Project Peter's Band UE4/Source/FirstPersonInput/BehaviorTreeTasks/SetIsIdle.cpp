// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ShadowAnna/Animation/AnnaAnimInstance.h"
#include "SetIsIdle.h"


EBTNodeResult::Type USetIsIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	AActor* AnnaActor = OwnerComp.GetBlackboardComponent()->GetOwner();

	if (AnnaActor)
	{
		UAnimInstance* AnnaBaseAnim = Cast<AController>(AnnaActor)->GetCharacter()->GetMesh()->GetAnimInstance();
		
		if (AnnaBaseAnim)
		{
			UAnnaAnimInstance* AnnaAnim = Cast<UAnnaAnimInstance>(AnnaBaseAnim);
			
			if (AnnaAnim)
			{
				//AnnaAnim->bIsIdle = bIdleActive;

				EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}




