// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "TestPlayerController.h"


//-----------------------------------------------------------------------------------------------
ATestPlayerController::ATestPlayerController( const FObjectInitializer& objectInitializer )
	: Super( objectInitializer )
{
	bShowMouseCursor = 1;
	DefaultMouseCursor = EMouseCursor::Type::Crosshairs;
	
}


//-----------------------------------------------------------------------------------------------

