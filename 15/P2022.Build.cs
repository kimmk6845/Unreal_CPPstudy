// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P2022 : ModuleRules
{
	public P2022(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Niagara" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
