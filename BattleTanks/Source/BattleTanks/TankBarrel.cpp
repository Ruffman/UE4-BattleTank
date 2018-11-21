// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"




void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = this->RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinPitchDegrees, MaxPitchDegrees);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}
