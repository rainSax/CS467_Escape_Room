// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CS467_Escape_RoomEditorTarget : TargetRules
{
	public CS467_Escape_RoomEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "CS467_Escape_Room" } );
	}
}
