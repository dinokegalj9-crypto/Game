// Copyright Hollow Crown Studio. All Rights Reserved.

using UnrealBuildTool;

public class HollowCrown : ModuleRules
{
	public HollowCrown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTasks",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Niagara"
		});

		// Public include path so headers can be included as "Combat/HCCombatComponent.h" etc.
		PublicIncludePaths.AddRange(new string[] { "HollowCrown" });
	}
}
