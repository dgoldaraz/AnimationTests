// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_IntertialOffset.generated.h"

class USkeletalMeshComponent;

/**
 * Custom node that apply offset to a bone based on character speed, simulating inertia
 */
USTRUCT()
struct ANIMATIONTESTS_API FAnimNode_IntertialOffset : public FAnimNode_SkeletalControlBase
{
	GENERATED_BODY()
};
