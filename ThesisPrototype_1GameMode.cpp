// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "ThesisPrototype_1GameMode.h"

#include "TestSpectatorPawn.h"
#include "TestPlayerController.h"
#include "GameHUD.h"


//-----------------------------------------------------------------------------------------------
AThesisPrototype_1GameMode::AThesisPrototype_1GameMode( const FObjectInitializer& objectInitializer )
	: Super( objectInitializer )
{
	DefaultPawnClass		= ATestSpectatorPawn::StaticClass();
	PlayerControllerClass	= ATestPlayerController::StaticClass();
	HUDClass				= AGameHUD::StaticClass();
}