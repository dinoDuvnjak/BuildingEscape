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

	PressurePlate = nullptr; //u pressureplate mozemo dodavati elmente Trigger volume.
	Owner = nullptr;

	TriggerMass = 0.0f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Find the owning actor
	Owner = GetOwner(); //declaring a pointer to an actor.

}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	OnClose.Broadcast();

	if (GetTotalMassOFActorsOnPlate() >= TriggerMass)
		OnOpen.Broadcast();
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
		//UE_LOG(LogTemp, Warning, TEXT("Overlapping component : %s"), *Actor->GetName());
	}

	return TotalMass;
}

