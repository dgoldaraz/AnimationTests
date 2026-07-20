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
	
	if (FProxyCombatGameplayData* proxyData = GetControlRigProxyOnGameThread())
	{
		// Calculate variables based on proxy
		// Calculate Lean based on proxy values
		

		
		float SpeedFactor = FMath::Clamp(proxyData->HorizontalVelocity / LeanClamp, 0.0f, 1.0f);
		switch (LeanType)
		{
		case ELeanType::UseTurnRate:
			{
				// YawDelta is difference per frame, conver it into degrees per second
				float TurnRate = proxyData->YawDelta / DeltaSeconds;
				// Normalize target lean based on MaxTurnValue, so we can use a [-1,1] blendspace
				float TargetLean = TurnRate / MaxTurnRate;
				TargetLean *= SpeedFactor;
				TargetLean = FMath::Clamp(TargetLean, -1.0, 1.0f);
				LeanValue = FMath::FInterpTo(LeanValue, TargetLean, DeltaSeconds, LeanBlendSpeed);
				// If YawDelta is too noisy, we can smooth it like
				// SmoothedTurnRate = FMath::FInterpTo(SmoothedTurnRate,TurnRate,DeltaTime,15.f);
				break;
			}
		default:
		case ELeanType::BasicInterpolation:
			{
				// Use YawDelta based on speed (more speed more lean)
				// If yaw delta is too noisy, can be smooth with FInterpTo
				// Lerp changes
				float TargetLean = FMath::Clamp(proxyData->YawDelta * SpeedFactor, -1.0f, 1.0f);
				LeanValue = FMath::FInterpTo(LeanValue, TargetLean, DeltaSeconds, LeanBlendSpeed);
				break;
			}
		}
	}
}

FAnimInstanceProxy* UCombatAnimInstance::CreateAnimInstanceProxy()
{
	return new FProxyCombatGameplayData(this);
}
