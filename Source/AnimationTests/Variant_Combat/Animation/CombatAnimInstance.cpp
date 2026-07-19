// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAnimInstance.h"

#include "CombatCharacter.h"

void FProxyCombatGameplayData::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	FAnimInstanceProxy::PreUpdate(InAnimInstance, DeltaSeconds);
	
	if (InAnimInstance != nullptr)
	{
		// Update Proxy values like - BIsAttacking, Yaw Delta rotation and horizontal Speed
		if (ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(InAnimInstance->GetOwningActor()))
		{
			bIsAttacking = CombatCharacter->GetIsAttacking();
			// Define how much the character should lean left or right
			YawDelta = CombatCharacter->GetYawDelta();
			// define if the character needs to lean at all
			HorizontalVelocity = CombatCharacter->GetHorizontalSpeed();
		}
	}
}

void UCombatAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	// Calculate variables based on proxy
	// Calculate Lean based on proxy values
}

FAnimInstanceProxy* UCombatAnimInstance::CreateAnimInstanceProxy()
{
	return new FProxyCombatGameplayData(this);
}
