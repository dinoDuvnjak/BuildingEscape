// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	//ovako radimo Upropery makro elemente, treba biti pazljiv s njima jel nemamo autocomplete imoraju biti tocno iznad propertija.
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr; //u pressureplate mozemo dodavati elmente Trigger volume.

	UPROPERTY(EditAnywhere)
		float DoorClosedDelay;

	float LastDoorOpenTime;

	AActor* Owner = nullptr;
	
	float GetTotalMassOFActorsOnPlate();
};
