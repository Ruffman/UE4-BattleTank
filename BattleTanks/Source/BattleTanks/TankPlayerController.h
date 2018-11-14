// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.35;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;

	void AimAtCrosshair() const;

	//Get world location of a linetrace through our crosshair, returns true if hit
	bool GetSightRayHitLocation(FVector& OUT HitLocation) const;

	bool GetLookDirection(FVector2D CrosshairScreenLocation, FVector& OUT LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OUT HitLocation) const;
};
