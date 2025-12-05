// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MGP_2425 : ModuleRules
{
	public MGP_2425(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
