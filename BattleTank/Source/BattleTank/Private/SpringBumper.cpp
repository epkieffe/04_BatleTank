// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringBumper.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"


// Sets default values
ASpringBumper::ASpringBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(SpringConstraint);

	Bumper = CreateDefaultSubobject<USphereComponent>(FName("Bumper"));
	Bumper->SetupAttachment(Axle);

	WheelConstraint	= CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASpringBumper::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();

}

void ASpringBumper::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	WheelConstraint->SetConstrainedComponents(Axle, NAME_None, Bumper, NAME_None);
}

// Called every frame
void ASpringBumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

