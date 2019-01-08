// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void WishForward(float Throw);

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void WishTurn(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UPROPERTY(BlueprintReadOnly, Category = "State")
		int CurrentSpeed = 0;
	
private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
