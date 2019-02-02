// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close the AI tank can get in cm
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 7500;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPossessedTankDeath();

};
