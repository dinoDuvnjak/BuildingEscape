// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	Owner = GetOwner(); //declaring a pointer to an actor.

}

///SAMO PRIMJER KAKO VRSITI ROTACIJU SA KODOM PREMDA JE PUNO LAKSE TO RADITI SA BLU[RITOM JEL IMA UGRADJEN TIMELINE SA BAZIERE CURVE
//void UOpenDoor::OpenDoor()
//{
//	// Set the door rotation
//	///Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));//Openangle is a value for a yaw
//	OnOpenRequest.Broadcast(); //sa bluerpintom smo radili rotaciju jel je puno jednostavije iyvesti nego sa kodom
//}
//
//void UOpenDoor::CloseDoor()
//{
//	// Create a rotator
//	// Set the door rotation
//	///Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
//	OnCloseRequest.Broadcast();
//}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	OnClose.Broadcast();

	if (GetTotalMassOFActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	
}

float UOpenDoor::GetTotalMassOFActorsOnPlate()
{
	float TotalMass = 0.f;
	
	//Find all the overlapping actors
	TArray<AActor*> OverLappingActors;
	if (!PressurePlate) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("No pressure plate component on a : %s"), *(GetOwner()->GetName()));
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for (auto& Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Overlaping component : %s"), *Actor->GetName());
	}

	return TotalMass;
}

