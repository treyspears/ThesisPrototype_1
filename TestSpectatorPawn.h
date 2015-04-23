// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "TestSpectatorPawn.generated.h"

#pragma region TestSpectorPawn States

class ATestSpectatorPawn;

namespace TestSpectatorPawn_State
{

	class Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) = 0;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) = 0;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) = 0;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) = 0;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) = 0;

	};


	class FirstPersonFlying : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) override;

		static TestSpectatorPawn_State::Base* EnterState();

	private:

		static FirstPersonFlying singleton;

		FirstPersonFlying() {};

		FirstPersonFlying( FirstPersonFlying const& );
		void operator=( FirstPersonFlying const& );
	};


	class FirstPersonOrbit : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) override;

		static TestSpectatorPawn_State::Base* EnterState();

	private:

		static FirstPersonOrbit singleton;

		FirstPersonOrbit() {};

		FirstPersonOrbit( FirstPersonOrbit const& );
		void operator=( FirstPersonOrbit const& );
	};


	class TopDownUnAttached : public TestSpectatorPawn_State::Base
	{
		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) override;

		static TestSpectatorPawn_State::Base* EnterState();

	private:

		static TopDownUnAttached singleton;

		TopDownUnAttached() {};

		TopDownUnAttached( TopDownUnAttached const& );
		void operator=( TopDownUnAttached const& );
	};


	class TopDownAttached : public TestSpectatorPawn_State::Base
	{
		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) override;

		static TestSpectatorPawn_State::Base* EnterState();

	private:

		static TopDownAttached singleton;

		TopDownAttached() {};

		TopDownAttached( TopDownAttached const& );
		void operator=( TopDownAttached const& );
	};


	class Locked : public TestSpectatorPawn_State::Base
	{
	public:

		virtual void MoveForward( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveRight( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void MoveUp_World( ATestSpectatorPawn* pawn, float Val ) override;
		virtual void TurnAtRate( ATestSpectatorPawn* pawn, float Rate ) override;
		virtual void LookUpAtRate( ATestSpectatorPawn* pawn, float Rate ) override;

		static TestSpectatorPawn_State::Base* EnterState();

	private:

		static Locked singleton;

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

	virtual void Tick( float DeltaSeconds ) override; 

	//-----------------------------------------------------------------------------------------------
	virtual void MoveForward( float Val ) override;
	virtual void MoveRight( float Val ) override;
	virtual void MoveUp_World( float Val ) override;
	void TurnAtRate( float Rate );
	void LookUpAtRate( float Rate );

	void SetState( class TestSpectatorPawn_State::Base* const newState );

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent()		const { return TopDownCameraComponent; }

	/** First person camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	class UCameraComponent* FirstPersonCameraComponent;

	/** Top down camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	class UCameraComponent* TopDownCameraComponent;

	/** If we're in orbit mode, the target we're orbiting*/
	TWeakPtr< AActor > CurrentOrbitTarget;

	/** Cached distance to orbit target, will need to re-compute if zoom-level is changed. */
	FVector			   DistanceToOrbitTarget;

protected:

	virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;

private:

	class TestSpectatorPawn_State::Base* currentState;
};


