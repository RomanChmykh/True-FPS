// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class FPS : ModuleRules
{
    public FPS(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        {
            "FPS/Public/Core",
            "FPS/Public/Character",
            "FPS/Public/Components"
        });
    }
}
