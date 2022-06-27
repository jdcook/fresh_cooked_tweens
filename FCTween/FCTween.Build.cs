using System.IO;
using UnrealBuildTool;

public class FCTween : ModuleRules
{
	public FCTween(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine" });
	}
}