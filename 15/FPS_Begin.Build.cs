// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_Begin : ModuleRules
{
	public FPS_Begin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "NavigationSystem", "GameplayTasks" });

		PublicIncludePaths.Add(ModuleDirectory);    // ������Ʈ ���� �������� ����� �ҷ����̰ڴٴ� �ǹ�
	}
}
