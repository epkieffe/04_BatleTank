// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

/*	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* BarrelToSet); // may be useful for swapping barrels

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* TurretToSet);*/

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

private:	
	// Called to bind functionality to input
	// TODO marked for deletion
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay()  override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	float RelaodTimeInSeconds = 3;

	double LastFireTime = -3;

};
