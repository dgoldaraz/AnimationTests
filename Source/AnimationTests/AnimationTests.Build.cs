// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnimationTests : ModuleRules
{
	public AnimationTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"MotionWarping",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AnimGraphRuntime"
		});

		PublicIncludePaths.AddRange(new string[] {
			"AnimationTests",
			"AnimationTests/Variant_Platforming",
			"AnimationTests/Variant_Platforming/Animation",
			"AnimationTests/Variant_Combat",
			"AnimationTests/Variant_Combat/AI",
			"AnimationTests/Variant_Combat/Animation",
			"AnimationTests/Variant_Combat/Gameplay",
			"AnimationTests/Variant_Combat/Interfaces",
			"AnimationTests/Variant_Combat/UI",
			"AnimationTests/Variant_SideScrolling",
			"AnimationTests/Variant_SideScrolling/AI",
			"AnimationTests/Variant_SideScrolling/Gameplay",
			"AnimationTests/Variant_SideScrolling/Interfaces",
			"AnimationTests/Variant_SideScrolling/UI"
		});

		// Easy way to test AnimGraph Nodes on Editor
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"UnrealEd",
				"AnimGraph",
				"BlueprintGraph"
			});
		}
		

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
