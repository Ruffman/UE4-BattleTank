// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"




void UTankTrack::SetThrottle(float Throttle)
{
	//TODO clamp actual throttle value so player can't overdrive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetAttachmentRoot());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}