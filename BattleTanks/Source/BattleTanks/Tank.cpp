// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"
#include "TankBarrel.h"


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
	AimingComponent->SetBarrelComponent(BarrelToSet);
}

void ATank::SetTurretComponent(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurretComponent(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed fire button"));
}