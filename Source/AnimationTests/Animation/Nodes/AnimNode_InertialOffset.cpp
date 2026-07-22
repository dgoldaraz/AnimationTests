// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNode_InertialOffset.h"

#include "Animation/AnimInstanceProxy.h"

FAnimNode_InertialOffset::FAnimNode_InertialOffset()
{
	CurrentOffset = FVector::ZeroVector;
	CurrentOffsetVelocity = FVector::ZeroVector;
	PrevVelocity = FVector::ZeroVector;
}

void FAnimNode_InertialOffset::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(InitializeBoneReferences);
	
	FAnimNode_SkeletalControlBase::InitializeBoneReferences(RequiredBones);
	//Initialize Bone
	BoneToApply.Initialize(RequiredBones);
}

bool FAnimNode_InertialOffset::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return BoneToApply.IsValidToEvaluate(RequiredBones);
}

void FAnimNode_InertialOffset::EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(EvaluateComponentSpaceInternal);
	FAnimNode_SkeletalControlBase::EvaluateComponentSpaceInternal(Context);
	
	// Get index of Bone
	const FBoneContainer& boneContainer = Context.Pose.GetPose().GetBoneContainer();
	FCompactPoseBoneIndex compactBoneIndex = BoneToApply.GetCompactPoseIndex(boneContainer);
	
	if (compactBoneIndex != INDEX_NONE)
	{
		// Get Component transform of the bone
		FTransform boneTransform = Context.Pose.GetComponentSpaceTransform(compactBoneIndex);
	
		// Apply Offset to transform
		boneTransform.AddToTranslation(CurrentOffset);
	
		// Return updated bone transform
		Context.Pose.SetComponentSpaceTransform(compactBoneIndex, boneTransform);
	}
}

void FAnimNode_InertialOffset::UpdateInternal(const FAnimationUpdateContext& Context)
{
	FAnimNode_SkeletalControlBase::UpdateInternal(Context);
	
	// Calculate new offset using intertia logic
	// Force calculation comes like
	// Ft = (-a) - K*x - C * v
	// where a is acceleration, x if offset and v offset velocity 
	// K is stiffness and C is damping
	
	const float DeltaTime = Context.GetDeltaTime();
	if (DeltaTime <= 0.0f)
	{
		return;
	}
	
	//Calculate current Velocity
	FVector characterAcc = (PrevVelocity - CharacterVelocity) / DeltaTime;
	// Update Velocity
	PrevVelocity = CharacterVelocity;
	
	//Calculate local space acceleration
	FTransform componentTransform = Context.AnimInstanceProxy->GetComponentTransform();
	FVector localAcc = componentTransform.InverseTransformVectorNoScale(characterAcc);
	
	// Resolve spring-damper algorithm
	FVector springForce = -Stiffness * CurrentOffset;
	FVector damperForce = -Damping * CurrentOffsetVelocity;
	
	FVector finalAcc = -localAcc + springForce + damperForce;
	
	// Update values from acceleration 
	CurrentOffsetVelocity += finalAcc * DeltaTime;
	CurrentOffset += CurrentOffsetVelocity * DeltaTime;
	
	// Finally, clamp offset to Max to avoid extreme changes
	CurrentOffset = CurrentOffset.GetClampedToMaxSize(MaxOffset);
}
