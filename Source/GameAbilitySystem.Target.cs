// Copyright yu kai

using UnrealBuildTool;
using System.Collections.Generic;

public class GameAbilitySystemTarget : TargetRules
{
	public GameAbilitySystemTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "GameAbilitySystem" } );
	}
}
