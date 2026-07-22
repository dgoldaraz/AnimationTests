// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimGraphNode_IntertialOffset.h"

#if WITH_EDITOR
FText UAnimGraphNode_IntertialOffset::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("Inertial Bone Offset"));
}

FString UAnimGraphNode_IntertialOffset::GetNodeCategory() const
{
	return TEXT("Custom Procedural Animation Test");
}

FText UAnimGraphNode_IntertialOffset::GetTooltipText() const
{
	return FText::FromString(TEXT("Apply procedural intertia movement on a bone based on character acceleration"));
}
#endif

