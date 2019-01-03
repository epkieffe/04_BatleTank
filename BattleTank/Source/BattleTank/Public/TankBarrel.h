// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void  Elevate(FVector WishAngleWithDeltaTime); // encoded as yaw, pitch, time
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 15;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 45;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;
	
};
