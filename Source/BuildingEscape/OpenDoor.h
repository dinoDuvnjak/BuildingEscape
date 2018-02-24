// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);  //blueprint assignable class


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintAssignable)// to be assigned to a blueprint
	FDoorRequest OnOpen; // initialization of the class

	UPROPERTY(BlueprintAssignable)// to be assigned to a blueprint
	FDoorRequest OnClose; // initialization of the class

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	//ovako radimo Upropery makro elemente, treba biti pazljiv s njima jel nemamo autocomplete imoraju biti tocno iznad propertija.
	UPROPERTY(EditAnywhere)
	float TriggerMass;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate; //u pressureplate mozemo dodavati elmente Trigger volume.

	AActor* Owner;
	
	float GetTotalMassOFActorsOnPlate();
};
