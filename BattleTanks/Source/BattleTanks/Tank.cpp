// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector AimLocation)
{
	if (!AimingComponent) { return; }
	AimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetBarrelComponent(UTankBarrel* BarrelToSet)
{
	TankBarrel = BarrelToSet;
	AimingComponent->SetBarrelComponent(BarrelToSet);
}

void ATank::SetTurretComponent(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurretComponent(TurretToSet);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (bIsReloaded)
	{
		if (!TankBarrel) { return; }
		AProjectile* ShotProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, TankBarrel->GetSocketTransform(FName(TEXT("LaunchLocation"))));

		if (!ShotProjectile) { return; }
		ShotProjectile->InitVelocity(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}