// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Find the owning actor
	OwnerRotation = GetOwner(); //declaring a pointer to an actor.

	//Get the player or in this case pawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // a pawn is an actor so it inherits from an actor

}

void UOpenDoor::OpenDoor()
{
	// Set the door rotation
	OwnerRotation->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));//Openangle is a value for a yaw
}

void UOpenDoor::CloseDoor()
{
	// Create a rotator
	// Set the door rotation
	OwnerRotation->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorClosedDelay)
	{
		CloseDoor();
	}

	
}

