// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay(); // super is an inheritance to an engine saying " Do this first in up inheritance"

	FString ObjectName = GetOwner()->GetName(); //get owner returns the pointer and then we call the method to get a name it return a string, you can look it on hover

	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString(); // kada vraca pointer onda koristimo -> kada vraca objekat onda .

	//Unreal log
	// For loging with text we have to *dereference pointer because unreal expects TCHAR array and we need to covert it to a string and %s more info https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);

	// ...
	
}


// Called every frame
void UPositionReporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

