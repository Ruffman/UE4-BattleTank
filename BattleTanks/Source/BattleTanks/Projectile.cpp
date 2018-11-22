// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("MoveComp")));
	MovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::InitVelocity(float Velocity)
{
	if (!MovementComponent) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Spawn proj with: %f"), Velocity);
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Velocity);
	MovementComponent->Activate();
}
