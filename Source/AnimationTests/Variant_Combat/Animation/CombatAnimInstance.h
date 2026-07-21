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
	
	// Store if player it's attacking
	bool bIsAttacking = false;
	// Current Yaw rotation
	float YawDelta = 0.0f;
	// Horizontal Velocity
	float HorizontalVelocity = 0.0f;
};

UENUM(BlueprintType)
enum class ELeanType : uint8
{
	BasicInterpolation,
	UseTurnRate,
};

UCLASS()
class ANIMATIONTESTS_API UCombatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
private:
	
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;
	
protected:
	// Define how much we should Lean
	UPROPERTY(BlueprintReadOnly)
	float LeanValue = 0.0f;
	
	// Lean Type
	UPROPERTY(EditAnywhere, Category = "Lean")
	ELeanType LeanType = ELeanType::BasicInterpolation;
	
	// Clamp rotation based on this float. This float controls how quickly the character reaches the Max Lean.
	UPROPERTY(EditAnywhere, Category = "Lean")
	float LeanClamp = 300.0f;
	
	// Speed of blend when calculating rotation, so sudden changes of rotation doesn't drive animation too hard
	UPROPERTY(EditAnywhere, Category = "Lean")
	float LeanBlendSpeed = 6.0f;
	
	// Maximum expected turn rate
	UPROPERTY(EditAnywhere, Category = "Lean")
	float MaxTurnRate = 600.0f;
	
private:
	// Create custom proxy
	FProxyCombatGameplayData ProxyCombatGameplayData;
};
