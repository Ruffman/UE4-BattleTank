// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair() const
{
	FVector HitLocation;
	if (!GetSightRayHitLocation(HitLocation)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("HitLocation at: %s!"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	//crosshair position in pixel coordinates
	FVector2D CrosshairScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (!GetLookDirection(CrosshairScreenLocation, LookDirection)) { return false; }

	if (!GetLookVectorHitLocation(LookDirection, OUT HitLocation)) { return false; }

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairScreenLocation, FVector& OUT LookDirection) const
{
	FVector LookLocation;
	if (!DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, LookLocation, LookDirection)) { return false; }
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OUT HitLocation) const
{
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	FHitResult HitResult = FHitResult(ForceInit);

	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + LookDirection * LineTraceRange;

	if(!GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		TraceParams)) 
	{ 
		HitLocation = FVector(0.0, 0.0, 0.0);
		return false; 
	}

	HitLocation = HitResult.ImpactPoint;
	return true;
}

