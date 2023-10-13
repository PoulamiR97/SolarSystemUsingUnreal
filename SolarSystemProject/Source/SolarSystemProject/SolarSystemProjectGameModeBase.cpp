// Copyright Epic Games, Inc. All Rights Reserved.


#include "SolarSystemProjectGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawnAttachedCamera.h"

ASolarSystemProjectGameModeBase::ASolarSystemProjectGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPawnAttachedCamera::StaticClass();
}
