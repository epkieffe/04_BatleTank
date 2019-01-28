// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

//Forward Declarations
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet,
			UTankTurret* TurretToSet);

/*	void SetBarrelReference(UTankBarrel* BarrelToSet); //may be useful for swapping barrels

	void SetTurretReference(UTankTurret* TurretToSet);*/

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	bool IsBarrelLocked();

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetAmmoCount() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Aiming;

	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000; //TODO find sensible value

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LockTolerance = 0.999; //TODO find sensible value

	FVector LaunchDirection = FVector(0);

	virtual void TickComponent(float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction) override;
	
	void MoveWeapon(FVector LaunchDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 10;

	double LastFireTime = 0;

};
