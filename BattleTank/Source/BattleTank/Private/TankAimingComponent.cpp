// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime,
	enum ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!ensure(Barrel)) { return; }
	if (AmmoCount < 1) { FiringState = EFiringState::OutOfAmmo; }
	else if ((FPlatformTime::Seconds() - LastFireTime) < Barrel->CooldownSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelLocked()) { FiringState = EFiringState::Locked; }
	else { FiringState = EFiringState::Aiming; }
	
}

int UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

/* May be useful for swapping barrels
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
*/

bool UTankAimingComponent::IsBarrelLocked()
{
	if (!ensure(Barrel)) { return false; }
	if (FVector::DotProduct(LaunchDirection, Barrel->GetForwardVector()) > LockTolerance)
	{
		return true;
	}
	else { return false; }
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	auto OutLaunchVelocity = FVector(0);

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
	}
}

void UTankAimingComponent::MoveWeapon(FVector LaunchDirection)
{
	FVector WishAngleWithDeltaTime;
	WishAngleWithDeltaTime.X = LaunchDirection.Rotation().Yaw;
	WishAngleWithDeltaTime.Y = LaunchDirection.Rotation().Pitch;
	WishAngleWithDeltaTime.Z = GetWorld()->DeltaTimeSeconds;

	auto SocketElevation = Turret->GetSocketRotation(FName("Barrel")).Pitch;

	Barrel->Elevate(WishAngleWithDeltaTime);
	Turret->Rotate(WishAngleWithDeltaTime);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(
				FName("Projectile")),
			Barrel->GetSocketRotation(
				FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		FiringState = EFiringState::Reloading;
		AmmoCount--;
	}
}
