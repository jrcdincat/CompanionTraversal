// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayer::SetForwardClimbVector(USplineComponent* splineComponent, float distanceAlongSpline)
{
	check(splineComponent != nullptr);
	FVector rightVectorAtSplineLocation = splineComponent->GetRightVectorAtDistanceAlongSpline(distanceAlongSpline, ESplineCoordinateSpace::World);
	FVector currentPlayerForwardVector = GetActorForwardVector();
	FRotator currentPlayerRotation = GetActorRotation();
	// Change players forward vector to match the right vectors direction
	FQuat newLocalRotation;
	FQuat rotationBetweenVectors = newLocalRotation.FindBetweenVectors(currentPlayerForwardVector, rightVectorAtSplineLocation);
	AddActorLocalRotation(rotationBetweenVectors);
}

