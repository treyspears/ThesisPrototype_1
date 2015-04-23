// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisPrototype_1.h"
#include "AdvertisementComponent.h"


// Sets default values for this component's properties
UAdvertisementComponent::UAdvertisementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UAdvertisementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UAdvertisementComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

