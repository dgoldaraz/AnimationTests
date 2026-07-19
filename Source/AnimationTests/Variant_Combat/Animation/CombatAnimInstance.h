// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "CombatAnimInstance.generated.h"

/**
 * Custom Anim Instance class.
 * This example allow to create a custom combat anim instance with specific logic
 * One new logic added will be to create a Thread-Safe Data Proxy that store relevant info
 * 
 */

/** Proxy override for this UAnimInstance-derived class */
USTRUCT()
struct FProxyCombatGameplayData : public FAnimInstanceProxy
{
	GENERATED_BODY()

public:
	FProxyCombatGameplayData()
	{
	}

	FProxyCombatGameplayData(UAnimInstance* InAnimInstance)
		: FAnimInstanceProxy(InAnimInstance)
	{
	}
	
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	
	bool bIsAttacking = false;
	float YawDelta = 0.0f;
	float HorizontalVelocity = 0.0f;
	
};

UCLASS()
class ANIMATIONTESTS_API UCombatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	// Return Custom Proxy
	FProxyCombatGameplayData* GetControlRigProxyOnGameThread() { return &GetProxyOnGameThread <FProxyCombatGameplayData>(); }
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
protected:

	// Create custom Proxy
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	
	// Define how much we should Lean
	float LeanValue = 0.0f;
	
	// Clamp rotation based on this float. This float controls how quickly the character reaches the Max Lean.
	UPROPERTY(EditAnywhere, Category = "Lean")
	float LeanClamp = 300.0f;
	
	// Blend lean based on this value. This value defines when Lean will be applied (smoothly) based on Horizontal Speed
	UPROPERTY(EditAnywhere, Category = "Lean")
	float LeanBlend = 200.0f;
	
	// Speed of blend when calculating rotation, so sudden changes of rotation doesn't drive animation too hard
	UPROPERTY(EditAnywhere, Category = "Lean")
	float RotationBlendSpeed = 6.0f;
};
