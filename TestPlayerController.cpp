// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "TestPlayerController.h"
#include "TestSpectatorPawn.h"

//-----------------------------------------------------------------------------------------------
ATestPlayerController::ATestPlayerController( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Type::Crosshairs;

	TestPlayerController_State::FirstPerson::EnterState( this );
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::BeginPlay()
{
	APawn* PossessedPawn = GetPawnOrSpectator();

	if ( PossessedPawn )
	{
		PawnAsSpectatorPawn = Cast< ATestSpectatorPawn >( PossessedPawn );
	}
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::UpdateRotation( float DeltaTime )
{
	CurrentState->UpdateRotation( this, DeltaTime );
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction( "SelectActor", IE_Pressed, this, &ATestPlayerController::OnSelectActorPressed );
	InputComponent->BindAction( "SelectActor", IE_Released, this, &ATestPlayerController::OnSelectActorReleased );

	InputComponent->BindAction( "EnterFirstPersonView", IE_Released, this, &ATestPlayerController::OnEnterFirstPersonView );
	InputComponent->BindAction( "EnterTopDownView", IE_Released, this, &ATestPlayerController::OnEnterTopDownView );
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::OnSelectActorPressed()
{
	CurrentState->OnSelectActorPressed( this );
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::OnSelectActorReleased()
{
	CurrentState->OnSelectActorReleased( this );	
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::OnEnterFirstPersonView()
{
	TestPlayerController_State::FirstPerson::EnterState( this );

	if ( PawnAsSpectatorPawn.IsValid() )
	{
		PawnAsSpectatorPawn->OnEnterFirstPersonView();
	}
}

//-----------------------------------------------------------------------------------------------
void ATestPlayerController::OnEnterTopDownView()
{
	TestPlayerController_State::TopDown::EnterState( this );

	if ( PawnAsSpectatorPawn.IsValid() )
	{
		PawnAsSpectatorPawn->OnEnterTopDownView();
	}
}

#pragma region ATestPlayerController States

/*
	FirstPerson Implementation
*/

TestPlayerController_State::FirstPerson TestPlayerController_State::FirstPerson::Singleton;

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::FirstPerson::EnterState( ATestPlayerController* PlayerController )
{
	if ( PlayerController->GetCurrentState() != &Singleton )
	{
		PlayerController->bShowMouseCursor = false;

		TWeakObjectPtr< ATestSpectatorPawn > PCPawnAsTestSpectatorPawn = nullptr;

		if ( PlayerController->PawnAsSpectatorPawn.IsValid() )
		{
			PCPawnAsTestSpectatorPawn = PlayerController->PawnAsSpectatorPawn;
			ACameraActor* TopDownCamera = PCPawnAsTestSpectatorPawn->GetTopDownCameraActor();
			
			FRotator NewRotation = PCPawnAsTestSpectatorPawn->TopDownCameraRotation;

			const FRotator SupposedRotation = FRotator( -90.f, 90.f, 0.f );

			PlayerController->SetControlRotation( NewRotation );
		}

		PlayerController->SetViewTargetWithBlend( PlayerController->GetPawn(), 0.f );

		PlayerController->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::FirstPerson::OnSelectActorPressed( ATestPlayerController* PlayerController )
{

}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::FirstPerson::OnSelectActorReleased( ATestPlayerController* PlayerController )
{

}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::FirstPerson::UpdateRotation( ATestPlayerController* PlayerController, float DeltaTime )
{
	PlayerController->APlayerController::UpdateRotation( DeltaTime );
}


/*
	TopDown Implementation
*/

TestPlayerController_State::TopDown TestPlayerController_State::TopDown::Singleton;

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::TopDown::EnterState( ATestPlayerController* PlayerController )
{
	if ( PlayerController->GetCurrentState() != &Singleton )
	{
		PlayerController->bShowMouseCursor = true;

		TWeakObjectPtr< ATestSpectatorPawn > PCPawnAsTestSpectatorPawn = nullptr;

		if( PlayerController->PawnAsSpectatorPawn.IsValid() )
		{		
			ACameraActor* TopDownCameraActor = nullptr;
			
			PCPawnAsTestSpectatorPawn = PlayerController->PawnAsSpectatorPawn;
			TopDownCameraActor = PCPawnAsTestSpectatorPawn->GetTopDownCameraActor();

			PlayerController->SetViewTargetWithBlend( TopDownCameraActor );
		}

		PlayerController->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::TopDown::OnSelectActorPressed( ATestPlayerController* PlayerController )
{

}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::TopDown::OnSelectActorReleased( ATestPlayerController* PlayerController )
{
	PlayerController->GetHitResultUnderCursor( ECC_Visibility, false, PlayerController->LatestMouseClickResult );
}

//-----------------------------------------------------------------------------------------------
void TestPlayerController_State::TopDown::UpdateRotation( ATestPlayerController* PlayerController, float DeltaTime )
{

}

#pragma endregion