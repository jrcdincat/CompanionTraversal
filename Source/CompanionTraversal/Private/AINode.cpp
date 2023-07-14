// Fill out your copyright notice in the Description page of Project Settings.


#include "AINode.h"

// Sets default values
AAINode::AAINode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAINode::BeginPlay()
{
	Super::BeginPlay();
}

void AAINode::SetSplinePointLocations()
{
	// Update the location of the first and last point for the spline to match this nodes location and the connecting nodes
	for (auto& map : nodeToSplineMap)
	{
		AActor* node = map.Key;
		AActor* spline = map.Value;
		if (IsValid(node) && IsValid(spline))
		{
			USplineComponent* splineComponent = spline->GetComponentByClass<USplineComponent>();
			if (IsValid(splineComponent))
			{
				splineComponent->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World);
				splineComponent->SetLocationAtSplinePoint(splineComponent->GetNumberOfSplinePoints() - 1, node->GetActorLocation(), ESplineCoordinateSpace::World);
				Cast<AAINode>(node)->SetReferences(this, spline); // Set node and spline as reference to connecting node
				spline->RerunConstructionScripts();
			}
		}
	}

	// Update the location of the last point for the spline to match this nodes location
	for (auto& map : referenceNodeToSplineMap)
	{
		AActor* node = map.Key; 
		AActor* spline = map.Value;

		if (IsValid(node) && IsValid(spline))
		{
			USplineComponent* splineComponent = spline->GetComponentByClass<USplineComponent>();
			if (IsValid(splineComponent))
			{
				splineComponent->SetLocationAtSplinePoint(splineComponent->GetNumberOfSplinePoints() - 1, GetActorLocation(), ESplineCoordinateSpace::World);
				spline->RerunConstructionScripts();
			}
		}
	}
}

void AAINode::SetReferences(AActor* node, AActor* spline)
{
	referenceNodeToSplineMap.Add(node, spline);
}

// Called every frame
void AAINode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

