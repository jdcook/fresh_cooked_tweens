// MIT License - Copyright 2026 Jared Cook

using System.IO;
using UnrealBuildTool;

public class FCTween : ModuleRules
{
	public FCTween(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "UMG", "DeveloperSettings" });
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "RobertPennerEasing"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "PhaserEasing"));
	}
}