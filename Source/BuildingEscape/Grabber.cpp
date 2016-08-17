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
	FindPhysicsHandleComponent();
	FindInputComponent();	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//if the physics handle is attached
		//move the object that we're holding

	GetFirstPhysicsBodyInReach();

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Sada cu da te ugrabim"));

	// Line trace and Try to reach any actors with physics body collision channel set

	// If we hit something then attach a physics handle
	// TODO attach the physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Sada Pustam"));
	//TODO release physics handle
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); //trazimo komponentu od ownera,odnosno pawna na koji je ova scripta zakacena ovo se zove GENERIC SIGNATURE
	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("physics handle component missing on a %S object (grabber.cpp line 34)"), *(GetOwner()->GetName()));
	}
}

///Look for attached Input component (only appears at the runtime)
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // 4th parameter is the function name that we want to perform
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component missing on a %S object (grabber.cpp line 45)"), *(GetOwner()->GetName()));
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
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

	LogHitResult(Hit);
	return Hit;
}

// LOG what we have hit with our ray-cast
void UGrabber::LogHitResult(FHitResult Hit)
{
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) // na ovakvim pointerima uvijek koristiti if uvijet da provjerimo da li postoje posto unreal inace pukne
	{
		UE_LOG(LogTemp, Warning, TEXT("line trace hit %s"), *(ActorHit->GetName()));
	}
}

