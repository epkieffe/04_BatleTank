// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3;

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& TraceDirection) const;
};
