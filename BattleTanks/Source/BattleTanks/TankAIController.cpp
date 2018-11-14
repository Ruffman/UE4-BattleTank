// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO move to player
	AimAtPlayer();
	//TODO fire if ready
}

void ATankAIController::AimAtPlayer() const
{
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) { return; }

	FVector PlayerLocation = PlayerTank->GetActorLocation();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	ControlledTank->AimAt(PlayerLocation);
}
