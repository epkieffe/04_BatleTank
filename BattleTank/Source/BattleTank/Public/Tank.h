// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// called by engine when actor takes damage
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const & DamageEvennt,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// returns percentage of health wrt starting health range [0.f, 1,f]
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FTankDelegate OnDeath;

/*	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* BarrelToSet); // may be useful for swapping barrels

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* TurretToSet);*/

private:	
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay()  override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth; // Initialized in Begin Play

};
