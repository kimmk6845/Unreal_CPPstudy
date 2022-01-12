// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UOnline_CPP : ModuleRules
{
	public UOnline_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
