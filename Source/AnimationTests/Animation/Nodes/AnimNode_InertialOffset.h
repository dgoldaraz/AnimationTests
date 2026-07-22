// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_InertialOffset.generated.h"

class USkeletalMeshComponent;

/**
 * Custom node that apply offset to a bone based on character speed, simulating inertia
 */
USTRUCT()
struct ANIMATIONTESTS_API FAnimNode_InertialOffset : public FAnimNode_SkeletalControlBase
{
	GENERATED_BODY()
	
public:
	FAnimNode_InertialOffset();
	
	// From FAnimNode_SkeletalControlBase
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	// Works on Component(World) Space (related with Character/Mesh) (while EvaluateSkeletalControl_AnyThread works on Local Space (related with root bone))
	virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context) override;
	
private:
	// use this function to update for skeletal control base
	virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;

public:
	// Bone to apply interial offset
	UPROPERTY(EditAnywhere, Category="Settings")
	FBoneReference BoneToApply;
	
	// Current Character Velocity to use on inertia calculations
	// A possible update to this is having a proper custom AnimProxy that caches Velocity of Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))
	FVector CharacterVelocity = FVector::ZeroVector;
	
	// Constant that affect how the bone will return to its original position
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float Stiffness = 120.0f;
	
	// Constant that defines how energy is absorbed to avoid infinite moevement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float Damping = 10.0f;
	
	// Max applied offset on bone. To avoid extreme movements on bone
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float MaxOffset = 25.0f;
	
private:
	
	// Offset currently applied to affected bone
	FVector CurrentOffset = FVector::ZeroVector;
	// Velocity currently on affected bone
	FVector CurrentOffsetVelocity = FVector::ZeroVector;
	// Cache velocity on previous frame
	FVector PrevVelocity = FVector::ZeroVector;
};
