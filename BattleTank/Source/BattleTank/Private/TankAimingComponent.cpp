// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	auto OutLaunchVelocity = FVector(0);
	auto LaunchDirection = FVector(0);
	if (UGameplayStatics::SuggestProjectileVelocity(
			GetOwner(),
			OutLaunchVelocity,
			Barrel->GetSocketLocation(FName("Projectile")),
			HitLocation,
			LaunchSpeed,
			false,
			0.f, //collision radius
			0.f, //override gravity
			ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	{
		LaunchDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(LaunchDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *GetOwner()->GetName(), *LaunchDirection.ToString());
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{	//get current barrel orientation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	//get rotation to launchDirection
	//move barrel towards LaunchDirection
	return;
}
