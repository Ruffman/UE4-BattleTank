// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAimingComponent::SetBarrelComponent(UTankBarrel* BarrelToSet)
{
	TankBarrel = BarrelToSet;
}

void UAimingComponent::SetTurretComponent(UTankTurret* TurretToSet)
{
	TankTurret = TurretToSet;
}

void UAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (!TankBarrel) { return; }
	FVector LaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("LaunchLocation"));
	bool bFoundSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OUT LaunchVelocity,
		StartLocation,
		AimLocation, 
		LaunchSpeed, 
		false, 
		20.f, 
		0.f, 
		ESuggestProjVelocityTraceOption::DoNotTrace, 
		FCollisionResponseParams::DefaultResponseParam, 
		TArray<AActor*>(), 
		true);

	if (!bFoundSolution) { return; }

	FVector AimDirection = LaunchVelocity.GetSafeNormal();
	MoveBarrel(AimDirection);
}

void UAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotation = TankBarrel->GetForwardVector().ToOrientationRotator();
	FRotator AimDirectionRotator = AimDirection.ToOrientationRotator();
	FRotator DeltaRotator = AimDirectionRotator - BarrelRotation;

	if (!TankTurret) { return; }
	if (!TankBarrel) { return; }

	TankBarrel->ElevateBarrel(DeltaRotator.Pitch);
	TankTurret->RotateTurret(DeltaRotator.Yaw);
}
