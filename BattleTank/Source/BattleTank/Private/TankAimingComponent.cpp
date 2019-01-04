// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
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
		MoveWeapon(LaunchDirection);
		//MoveBarrel(LaunchDirection);
		//MoveTurret(LaunchDirection);
	}
}

void UTankAimingComponent::MoveWeapon(FVector LaunchDirection)
{
	FVector WishAngleWithDeltaTime;
	WishAngleWithDeltaTime.X = LaunchDirection.Rotation().Yaw;
	WishAngleWithDeltaTime.Y = LaunchDirection.Rotation().Pitch;
	WishAngleWithDeltaTime.Z = GetWorld()->DeltaTimeSeconds;

	Barrel->Elevate(WishAngleWithDeltaTime);
	Turret->Rotate(WishAngleWithDeltaTime);
}
