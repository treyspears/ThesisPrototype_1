// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "TestSpectatorPawn.generated.h"

class ACameraActor;

#pragma region TestSpectorPawn States

class ATestSpectatorPawn;

namespace TestSpectatorPawn_State
{

	class Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) = 0;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) = 0;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) = 0;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) = 0;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) = 0;

	};


	class FirstPersonFlying : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;

		static void EnterState( ATestSpectatorPawn* Pawn );

	private:

		static FirstPersonFlying Singleton;

		FirstPersonFlying() {};

		FirstPersonFlying( FirstPersonFlying const& );
		void operator=( FirstPersonFlying const& );
	};


	class FirstPersonOrbit : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;

		static void EnterState( ATestSpectatorPawn* Pawn );

	private:

		static FirstPersonOrbit Singleton;

		FirstPersonOrbit() {};

		FirstPersonOrbit( FirstPersonOrbit const& );
		void operator=( FirstPersonOrbit const& );
	};


	class TopDownUnAttached : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;

		static void EnterState( ATestSpectatorPawn* Pawn );

	private:

		static TopDownUnAttached Singleton;

		TopDownUnAttached() {};

		TopDownUnAttached( TopDownUnAttached const& );
		void operator=( TopDownUnAttached const& );
	};


	class TopDownAttached : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;

		static void EnterState( ATestSpectatorPawn* Pawn );

	private:

		static TopDownAttached Singleton;

		TopDownAttached() {};

		TopDownAttached( TopDownAttached const& );
		void operator=( TopDownAttached const& );
	};


	class Locked : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* Pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* Pawn, float Rate ) override;

		static void EnterState( ATestSpectatorPawn* Pawn );

	private:

		static Locked Singleton;

		Locked() {};

		Locked( Locked const& );
		void operator=( Locked const& );
	};

}

#pragma endregion

/**
 * 
 */
UCLASS()
class THESISPROTOTYPE_1_API ATestSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
public:

	ATestSpectatorPawn( const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override; 

	void InitializeCameras();
	
	virtual void MoveForward( float Val ) override;
	virtual void MoveRight( float Val ) override;
	virtual void MoveUp_World( float Val ) override;
	void TurnAtRate( float Rate );
	void LookUpAtRate( float Rate );

	void OnEnterFirstPersonView();
	void OnEnterTopDownView();

	FORCEINLINE void SetState( class TestSpectatorPawn_State::Base* const NewState );
	FORCEINLINE class TestSpectatorPawn_State::Base const* const GetCurrentState() const;

	FORCEINLINE ACameraActor* GetFirstPersonCameraActor() const; 
	FORCEINLINE ACameraActor* GetTopDownCameraActor() const;
	void MovePawnToTopDownCameraZPosition();

	/** First person camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	class UChildActorComponent* FirstPersonCameraComponent;

	/** Top down camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	class UChildActorComponent* TopDownCameraComponent;

	/** Rotation of the TopDown Camera. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Camera" )
	FRotator TopDownCameraRotation;
	
	/** Starting Z-Location of Top Down Camera */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Camera )
	float InitialTopDownCameraWorldZLocation;

	/** If we're in orbit mode, the target we're orbiting*/
	UPROPERTY()
	TWeakObjectPtr< AActor > CurrentOrbitTarget;

	/** Cached distance to orbit target, will need to re-compute if zoom-level is changed. */
	UPROPERTY()
	FVector DistanceToOrbitTarget;

protected:

	virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;

private:

	class TestSpectatorPawn_State::Base* CurrentState;
};

//-----------------------------------------------------------------------------------------------
FORCEINLINE void ATestSpectatorPawn::SetState( class TestSpectatorPawn_State::Base* const NewState )
{
	CurrentState = NewState;
}

//-----------------------------------------------------------------------------------------------
FORCEINLINE TestSpectatorPawn_State::Base const* const ATestSpectatorPawn::GetCurrentState() const
{
	return CurrentState;
}

//-----------------------------------------------------------------------------------------------
FORCEINLINE ACameraActor* ATestSpectatorPawn::GetFirstPersonCameraActor() const
{
	ACameraActor* result = nullptr;

	result = Cast< ACameraActor >( FirstPersonCameraComponent->ChildActor );

	return result;
}

//-----------------------------------------------------------------------------------------------
FORCEINLINE ACameraActor* ATestSpectatorPawn::GetTopDownCameraActor() const
{
	ACameraActor* result = nullptr;

	result = Cast< ACameraActor >( TopDownCameraComponent->ChildActor );

	return result;
}
