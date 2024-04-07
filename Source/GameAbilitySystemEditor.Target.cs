// Copyright yu kai

using UnrealBuildTool;
using System.Collections.Generic;

public class GameAbilitySystemEditorTarget : TargetRules
{
	public GameAbilitySystemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "GameAbilitySystem" } );
	}
}
