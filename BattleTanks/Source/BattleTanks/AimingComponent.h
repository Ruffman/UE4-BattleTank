// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"


class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector AimLocation, float LaunchSpeed);
	void SetBarrelComponent(UTankBarrel* BarrelToSet);
	void SetTurretComponent(UTankTurret* TurretToSet);

private:
	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	// Called when the game starts
	virtual void BeginPlay() override;

	// Sets default values for this component's properties
	UAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Moves the barrel towards a desired direction
	void MoveBarrel(FVector AimDirection);
};
