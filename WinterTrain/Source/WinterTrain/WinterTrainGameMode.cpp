// Copyright Epic Games, Inc. All Rights Reserved.

#include "WinterTrainGameMode.h"
#include "WinterTrainCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWinterTrainGameMode::AWinterTrainGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
