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

	PhysicsHandle = nullptr;
	InputComponent = nullptr;

	Reach = 100.f;
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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Pointer Protection
	if (!PhysicsHandle) { return; }
	//if the physics handle is attached - if we lift some object already
	if (PhysicsHandle->GrabbedComponent)
	{
		//move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	// Line trace and Try to reach any actors with physics body collision channel set
	auto HitResul =	GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResul.GetComponent();
	auto ActorHit = HitResul.GetActor();

	if (ActorHit)
	{
		if (PhysicsHandle == nullptr) { return; }
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
		OnGrab.Broadcast(); // TODO Do we need this??
	}

}

void UGrabber::Release()
{
	if (PhysicsHandle == nullptr) { return; }
	PhysicsHandle->ReleaseComponent();
}

// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	//Pointer Protection
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); //trazimo komponentu od ownera,odnosno pawna na koji je ova scripta zakacena ovo se zove GENERIC SIGNATURE

	if (PhysicsHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("physics handle component missing on a %S object (grabber.cpp line 34)"), *(GetOwner()->GetName()));
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
	//Line trace (AKA Ray-cast)out to reach distance
	//Setup query params
	FCollisionQueryParams TraceParamaters(FName(TEXT("")), false, GetOwner()); 
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		TraceParamaters
	);

	LogHitResult(HitResult);
	return HitResult;
}

// LOG what we have hit with our ray-cast
void UGrabber::LogHitResult(FHitResult Hit)
{
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("line trace hit %s"), *(ActorHit->GetName()));
	}
}

FVector UGrabber::GetReachLineEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("Location is %s, Rotation is a %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	// Draw a red trace in the world to visualize
	FVector LineTraceEnd = GetReachLineStart() + (GetThePlayerPointRotation().Vector() * Reach);
	return LineTraceEnd;
}

// Get the player view point every tick
FVector UGrabber::GetReachLineStart()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

// Get the player rotation point every tick
FRotator UGrabber::GetThePlayerPointRotation()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointRotation;
}

