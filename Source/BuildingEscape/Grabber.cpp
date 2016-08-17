// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT // we define out that is doing nothing just as a reminder that the values changes in engine program that we send as a function parameter.


// Sets default values for this component's properties
UGrabber::UGrabber() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber rreport to duty"));


	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // we used OUT paramater (don't do anything just as warning to us) macro to know that unreal engine changes the value that we send to the method. This is their error and our reminder.

	///UE_LOG(LogTemp, Warning, TEXT("Location is %s, Rotation is a %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()); //TODO LOG This out yourself.

	/// Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	
	///Line trace (AKA Ray-cast)out to reach distance
		///Setup query params
		FCollisionQueryParams TraceParamaters(FName(TEXT("")), false, GetOwner()); // last parameter we are for ignoring ourself.
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, 
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // u zagradama je tip enumerator, ovako mu pristupamo
		TraceParamaters
	);

	// See what we hit
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) // na ovakvim stvarim auvijek koristiti if uvijet da provjerimo da li postoje posto unreal inace pukne
	{
		UE_LOG(LogTemp, Warning, TEXT("tu sam"));
		UE_LOG(LogTemp, Warning, TEXT("line trace hit %s"), *(ActorHit->GetName())); 
	}

}

