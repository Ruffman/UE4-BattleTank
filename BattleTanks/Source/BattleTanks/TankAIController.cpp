// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) { return; }
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) { return; }
	
	//TODO move to player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}
