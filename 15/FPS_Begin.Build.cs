// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_Begin : ModuleRules
{
	public FPS_Begin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "NavigationSystem", "GameplayTasks" });

		PublicIncludePaths.Add(ModuleDirectory);    // 프로젝트 폴더 기준으로 헤더를 불러들이겠다는 의미
	}
}
