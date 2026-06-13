// Copyright Hollow Crown Studio. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HollowCrownTarget : TargetRules
{
	public HollowCrownTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("HollowCrown");
	}
}
