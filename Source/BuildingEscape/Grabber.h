// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	//The distance that our player can grab away from his body
	float Reach = 100.f;

	//The component attached on our player / pawn
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and reach what's in reach, called on key pressed
	void Grab();
	// Called on key released
	void Release();
	// Find (assumed) attached physics component
	void FindPhysicsHandleComponent();
	// Setup (assumed) attached input component
	void FindInputComponent();
	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// Log the name of the object that we hit 
	void LogHitResult(FHitResult Hit);
};
