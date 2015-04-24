// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

class ATestSpectatorPawn;

#pragma region TestPlayerController States

class ATestPlayerController;

namespace TestPlayerController_State
{

	class Base
	{
	public:

		virtual void OnSelectActorPressed( ATestPlayerController* PlayerController ) = 0;
		virtual void OnSelectActorReleased( ATestPlayerController* PlayerController ) = 0;
		virtual void UpdateRotation( ATestPlayerController* PlayerController, float DeltaTime ) = 0;
	};


	class FirstPerson : public TestPlayerController_State::Base
	{
	public:

		virtual void OnSelectActorPressed( ATestPlayerController* PlayerController ) override;
		virtual void OnSelectActorReleased( ATestPlayerController* PlayerController ) override;
		virtual void UpdateRotation( ATestPlayerController* PlayerController, float DeltaTime ) override;

		static void EnterState( ATestPlayerController* PlayerController );

	private:

		static FirstPerson Singleton;

		FirstPerson() {};

		FirstPerson( FirstPerson const& );
		void operator=( FirstPerson const& );
	};


	class TopDown : public TestPlayerController_State::Base
	{
	public:

		virtual void OnSelectActorPressed( ATestPlayerController* PlayerController ) override;
		virtual void OnSelectActorReleased( ATestPlayerController* PlayerController ) override;
		virtual void UpdateRotation( ATestPlayerController* PlayerController, float DeltaTime ) override;

		static void EnterState( ATestPlayerController* PlayerController );

	private:

		static TopDown Singleton;

		TopDown() {};

		TopDown( TopDown const& );
		void operator=( TopDown const& );
	};
}

#pragma endregion
/**
 * 
 */
UCLASS()
class THESISPROTOTYPE_1_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATestPlayerController( const FObjectInitializer& ObjectInitializer );
	
	virtual void BeginPlay() override;
	virtual void UpdateRotation( float DeltaTime ) override;
	
	void OnSelectActorPressed();
	void OnSelectActorReleased();

	void OnEnterFirstPersonView();
	void OnEnterTopDownView();

	FORCEINLINE void SetState( class TestPlayerController_State::Base* const NewState )	{ CurrentState = NewState; }
	FORCEINLINE class TestPlayerController_State::Base const* const GetCurrentState() const		{ return CurrentState; }

	FHitResult LatestMouseClickResult;
	TWeakObjectPtr< ATestSpectatorPawn > PawnAsSpectatorPawn; 

protected:

	virtual void SetupInputComponent() override;

private:

	class TestPlayerController_State::Base* CurrentState;
};
