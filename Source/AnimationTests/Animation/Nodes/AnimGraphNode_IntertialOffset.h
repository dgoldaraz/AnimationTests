// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#if WITH_EDITOR
#include "AnimNode_InertialOffset.h"
#include "Editor/AnimGraph/Public/AnimGraphNode_SkeletalControlBase.h"
#include "AnimGraphNode_IntertialOffset.generated.h"

/**
 * AnimGraph Node to use InterialOffset AnimNode
 */
UCLASS()
class ANIMATIONTESTS_API UAnimGraphNode_IntertialOffset : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()

public:
	// From UAnimGraphNode_SkeletalControlBase
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FString GetNodeCategory() const override;
	virtual FText GetTooltipText() const override;
	
protected:
	// Return AnimNode
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }
	
public:
#if WITH_EDITORONLY_DATA
	// Node to use for calculations
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_InertialOffset Node;
#endif
};

#endif