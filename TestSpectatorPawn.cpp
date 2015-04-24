// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "TestSpectatorPawn.h"
#include "Components/ChildActorComponent.h"

/*
	ATestSpectatorPawn Implementation
*/
//-----------------------------------------------------------------------------------------------
ATestSpectatorPawn::ATestSpectatorPawn( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
	, CurrentOrbitTarget( nullptr )
	, DistanceToOrbitTarget( FVector::ZeroVector )
	, InitialTopDownCameraWorldZLocation( 1024.f )
	, TopDownCameraRotation( -90.f, 90.f, 0.f )
	//, PawnZLocationBeforeEnteringTopDownView( GetActorLocation().Z )
{
	FirstPersonCameraComponent = CreateDefaultSubobject< UChildActorComponent >( TEXT( "First Person Camera" ) );
	FirstPersonCameraComponent->AttachParent = RootComponent;
	FirstPersonCameraComponent->ChildActorClass = ACameraActor::StaticClass();

	TopDownCameraComponent = CreateDefaultSubobject< UChildActorComponent >( TEXT( "Top Down Camera" ) );
	TopDownCameraComponent->AttachParent = RootComponent;
	TopDownCameraComponent->ChildActorClass = ACameraActor::StaticClass();

	static FName CollisionProfileName( TEXT( "NoCollision" ) );
	GetCollisionComponent()->SetCollisionProfileName( CollisionProfileName );

	TestSpectatorPawn_State::FirstPersonFlying::EnterState( this );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
	Super::SetupPlayerInputComponent( InputComponent );

	InputComponent->BindAxis( "TurnRate", this, &ATestSpectatorPawn::TurnAtRate );
	InputComponent->BindAxis( "LookUpRate", this, &ATestSpectatorPawn::LookUpAtRate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();

	InitializeCameras();
	
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::InitializeCameras()
{
	ACameraActor* ChildActorAsCameraActor = nullptr;

	ChildActorAsCameraActor = Cast< ACameraActor>( FirstPersonCameraComponent->ChildActor );

	if ( ChildActorAsCameraActor )
	{
		UCameraComponent* CameraComponent;
		CameraComponent = ChildActorAsCameraActor->GetCameraComponent();

		if ( CameraComponent )
		{
			CameraComponent->bUsePawnControlRotation = true;
			CameraComponent->bConstrainAspectRatio = false;
		}
	}

	ChildActorAsCameraActor = Cast< ACameraActor>( TopDownCameraComponent->ChildActor );

	if ( ChildActorAsCameraActor )
	{
		ChildActorAsCameraActor->SetActorRotation( TopDownCameraRotation );

		UCameraComponent* CameraComponent;
		CameraComponent = ChildActorAsCameraActor->GetCameraComponent();

		if ( CameraComponent )
		{
			CameraComponent->bUsePawnControlRotation = false;
			CameraComponent->bConstrainAspectRatio = false;
		}
	}
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveForward( float Val )
{
	CurrentState->MoveForward( this,  Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveRight( float Val )
{
	CurrentState->MoveRight( this, Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MoveUp_World( float Val )
{
	CurrentState->MoveUp_World( this, Val );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::TurnAtRate( float Rate )
{
	CurrentState->TurnAtRate( this, Rate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::LookUpAtRate( float Rate )
{
	CurrentState->LookUpAtRate( this, Rate );
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::OnEnterFirstPersonView()
{
	if( CurrentOrbitTarget.IsValid() )
	{
		TestSpectatorPawn_State::FirstPersonOrbit::EnterState( this );
	}
	else
	{
		TestSpectatorPawn_State::FirstPersonFlying::EnterState( this );
	}
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::OnEnterTopDownView()
{
	MovePawnToTopDownCameraZPosition();

	if ( CurrentOrbitTarget.IsValid() )
	{
		TestSpectatorPawn_State::TopDownAttached::EnterState( this );
	}
	else
	{
		TestSpectatorPawn_State::TopDownUnAttached::EnterState( this );
	}
}

//-----------------------------------------------------------------------------------------------
void ATestSpectatorPawn::MovePawnToTopDownCameraZPosition()
{
	FVector CameraLocation = GetActorLocation();
	CameraLocation.Z = InitialTopDownCameraWorldZLocation;

	SetActorLocation( CameraLocation );
}


#pragma region ATestSpectatorPawn States

/*
	FirstPersonFlying Implementation
*/

TestSpectatorPawn_State::FirstPersonFlying TestSpectatorPawn_State::FirstPersonFlying::Singleton;

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::EnterState( ATestSpectatorPawn* Pawn )
{

	if ( Pawn->GetCurrentState() != &Singleton )
	{
		Pawn->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveForward( ATestSpectatorPawn* Pawn, float Val )
{
	Pawn->ADefaultPawn::MoveForward( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveRight( ATestSpectatorPawn* Pawn, float Val )
{
	Pawn->ADefaultPawn::MoveRight( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::MoveUp_World( ATestSpectatorPawn* Pawn, float Val )
{
	Pawn->ADefaultPawn::MoveUp_World( Val );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::TurnAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
	Pawn->ADefaultPawn::TurnAtRate( Rate );
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonFlying::LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
	Pawn->ADefaultPawn::LookUpAtRate( Rate );
}



/*
FirstPersonOrbit Implementation
*/

TestSpectatorPawn_State::FirstPersonOrbit TestSpectatorPawn_State::FirstPersonOrbit::Singleton;

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::EnterState( ATestSpectatorPawn* Pawn )
{
	if ( Pawn->GetCurrentState() != &Singleton )
	{
		Pawn->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveForward( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveRight( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::MoveUp_World( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::TurnAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::FirstPersonOrbit::LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}



/*
TopDownUnAttached Implementation
*/

TestSpectatorPawn_State::TopDownUnAttached TestSpectatorPawn_State::TopDownUnAttached::Singleton;

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::EnterState( ATestSpectatorPawn* Pawn )
{
	if ( Pawn->GetCurrentState() != &Singleton )
	{
		Pawn->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveForward( ATestSpectatorPawn* Pawn, float Val )
{
	const FVector NorthVector( 0.f, 1.f, 0.f );

	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( NorthVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveRight( ATestSpectatorPawn* Pawn, float Val )
{
	const FVector WestVector( -1.f, 0.f, 0.f );

	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( WestVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::MoveUp_World( ATestSpectatorPawn* Pawn, float Val )
{
	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( FVector::UpVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::TurnAtRate( ATestSpectatorPawn* Pawn, float Rate )
{

}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownUnAttached::LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate )
{

}



/*
TopDownAttached Implementation
*/

TestSpectatorPawn_State::TopDownAttached TestSpectatorPawn_State::TopDownAttached::Singleton;

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::EnterState( ATestSpectatorPawn* Pawn )
{
	if ( Pawn->GetCurrentState() != &Singleton )
	{
		Pawn->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveForward( ATestSpectatorPawn* Pawn, float Val )
{
	const FVector NorthVector( 0.f, 1.f, 0.f );

	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( NorthVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveRight( ATestSpectatorPawn* Pawn, float Val )
{
	const FVector WestVector( -1.f, 0.f, 0.f );

	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( WestVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::MoveUp_World( ATestSpectatorPawn* Pawn, float Val )
{
	if ( Val != 0.f )
	{
		Pawn->AddMovementInput( FVector::UpVector, Val );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::TurnAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::TopDownAttached::LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}



/*
Locked Implementation
*/

TestSpectatorPawn_State::Locked TestSpectatorPawn_State::Locked::Singleton;

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::EnterState( ATestSpectatorPawn* Pawn )
{
	if ( Pawn->GetCurrentState() != &Singleton )
	{
		Pawn->SetState( &Singleton );
	}
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveForward( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveRight( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::MoveUp_World( ATestSpectatorPawn* Pawn, float Val )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::TurnAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}

//-----------------------------------------------------------------------------------------------
void TestSpectatorPawn_State::Locked::LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate )
{
}

#pragma endregion