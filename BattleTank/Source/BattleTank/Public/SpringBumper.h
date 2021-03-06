// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "SpringBumper.generated.h"

UCLASS()
class BATTLETANK_API ASpringBumper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringBumper();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Bumper = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* WheelConstraint = nullptr;
	
};
