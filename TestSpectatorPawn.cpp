// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "TestSpectatorPawn.h"

/*
	ATestSpectatorPawn Implementation
*/
//-----------------------------------------------------------------------------------------------
ATestSpectatorPawn::ATestSpectatorPawn( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
	, CurrentOrbitTarget( nullptr )
	, DistanceToOrbitTarget( FVector::ZeroVector )
{
	currentState = TestSpectatorPawn_State::FirstPersonFlying::EnterState();

	FirstPersonCameraComponent = CreateDefaultSubobject< UCameraComponent >( TEXT( "First Person Camera") );
	FirstPersonCameraComponent->AttachParent = RootComponent;
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	TopDownCameraComponent = CreateDefaultSubobject< UCameraComponent >( TEXT( "Top Down Camera" ) );
	TopDownCameraComponent->AttachParent = RootComponent;
	TopDownCameraComponent->bUsePawnControlRotation = false;

	TopDownCameraComponent->RelativeRotation = FRotator( -90.f, -90.f, 0.f );
	TopDownCameraComponent->RelativeLocation = FVector( 0.f, 0.f, 1024.f );

	static FName CollisionProfileName( TEXT( "NoCollision" ) );
	GetCollisionComponent()->SetCollisionProfileName( CollisionProfileName );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
	Super::SetupPlayerInputComponent( InputComponent );

	InputComponent->BindAxis( "TurnRate", this, &ATestSpectatorPawn::TurnAtRate );
	InputComponent->BindAxis( "LookUpRate", this, &ATestSpectatorPawn::LookUpAtRate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveForward( float Val )
{
	currentState->MoveForward( this,  Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveRight( float Val )
{
	currentState->MoveRight( this, Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveUp_World( float Val )
{
	currentState->MoveUp_World( this, Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::TurnAtRate( float Rate )
{
	currentState->TurnAtRate( this, Rate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::LookUpAtRate( float Rate )
{
	currentState->LookUpAtRate( this, Rate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::SetState( class TestSpectatorPawn_State::Base* const newState )
{
	if( currentState != newState )
	{
		currentState = newState;
	}
}


#pragma region ATestSpectatorPawn States

/*
	FirstPersonFlying Implementation
*/

TestSpectatorPawn_State::FirstPersonFlying TestSpectatorPawn_State::FirstPersonFlying::singleton;

//-----------------------------------------------------------------------------------------------
TestSpectatorPawn_State::Base* TestSpectatorPawn_State::FirstPersonFlying::EnterState()
{
	return &singleton;
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveForward( ATestSpectatorPawn* pawn, float Val )
{
	pawn->ADefaultPawn::MoveForward( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveRight( ATestSpectatorPawn* pawn, float Val )
{
	pawn->ADefaultPawn::MoveRight( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveUp_World( ATestSpectatorPawn* pawn, float Val )
{
	pawn->ADefaultPawn::MoveUp_World( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::TurnAtRate( ATestSpectatorPawn* pawn, float Rate )
{
	pawn->ADefaultPawn::TurnAtRate( Rate );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::LookUpAtRate( ATestSpectatorPawn* pawn, float Rate )
{
	pawn->ADefaultPawn::LookUpAtRate( Rate );
}



/*
FirstPersonOrbit Implementation
*/

TestSpectatorPawn_State::FirstPersonOrbit TestSpectatorPawn_State::FirstPersonOrbit::singleton;

//-----------------------------------------------------------------------------------------------
TestSpectatorPawn_State::Base* TestSpectatorPawn_State::FirstPersonOrbit::EnterState()
{
	return &singleton;
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveForward( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveRight( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveUp_World( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::TurnAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::LookUpAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}



/*
TopDownUnAttached Implementation
*/

TestSpectatorPawn_State::TopDownUnAttached TestSpectatorPawn_State::TopDownUnAttached::singleton;

//-----------------------------------------------------------------------------------------------
TestSpectatorPawn_State::Base* TestSpectatorPawn_State::TopDownUnAttached::EnterState()
{
	return &singleton;
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveForward( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveRight( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveUp_World( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::TurnAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::LookUpAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}



/*
TopDownAttached Implementation
*/

TestSpectatorPawn_State::TopDownAttached TestSpectatorPawn_State::TopDownAttached::singleton;

//-----------------------------------------------------------------------------------------------
TestSpectatorPawn_State::Base* TestSpectatorPawn_State::TopDownAttached::EnterState()
{
	return &singleton;
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveForward( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveRight( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveUp_World( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::TurnAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::LookUpAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}



/*
Locked Implementation
*/

TestSpectatorPawn_State::Locked TestSpectatorPawn_State::Locked::singleton;

//-----------------------------------------------------------------------------------------------
TestSpectatorPawn_State::Base* TestSpectatorPawn_State::Locked::EnterState()
{
	return &singleton;
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveForward( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveRight( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveUp_World( ATestSpectatorPawn* pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::TurnAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::LookUpAtRate( ATestSpectatorPawn* pawn, float Rate )
{
}

#pragma endregion