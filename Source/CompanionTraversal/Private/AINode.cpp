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

void AAINode::ConstructSpline()
{
	//UClass* spline = splineBlueprint->StaticClass();


	//if (spline && spline->IsChildOf(AActor::StaticClass()))
	//{
	//	a = CreateDefaultSubobject<AActor>(FName(TEXT("NewObject")), spline, spline, false, false);
	//}


	//FActorSpawnParameters spawnParams;
	//spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//if (IsValid(spline))
	//{
	//	if (IsValid(GetWorld()))
	//	{
	//		a = NewObject<AActor>(splineBlueprint, "Test", EObjectFlags::RF_Transactional);
	//		// a = GetWorld()->SpawnActor<AActor>(splineBlueprint, GetActorLocation(), GetActorRotation(), spawnParams);
	//	}
	//}

	//FVector selfLocation GetActorLocation();

	//const 
}

void AAINode::SetSplinePointLocations()
{
	// Update the location of the first and last point for the spline to match this nodes location and the connecting nodes
	for (auto& connnectedSpline : connectedSplines)
	{
		if (IsValid(connnectedSpline))
		{
			USplineComponent* splineComponent = connnectedSpline->GetComponentByClass<USplineComponent>();
			if (IsValid(splineComponent))
			{
				splineComponent->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World);

				for (auto& node : nodes)
				{
					if (IsValid(node))
					{
						splineComponent->SetLocationAtSplinePoint(splineComponent->GetNumberOfSplinePoints() - 1, node->GetActorLocation(), ESplineCoordinateSpace::World);
						Cast<AAINode>(node)->SetReferences(this, connnectedSpline);
					}
				}
				connnectedSpline->RerunConstructionScripts();
			}
		}
	}

	// Update the last point in the reference spline with this node
	for (auto& connectedRef : connectedReferences)
	{
		if (!connectedReferences.IsEmpty() && IsValid(connectedRef))
		{
			USplineComponent* splineComponent = connectedRef->GetComponentByClass <USplineComponent>();
			if (IsValid(splineComponent))
			{
				splineComponent->SetLocationAtSplinePoint(splineComponent->GetNumberOfSplinePoints() - 1, GetActorLocation(), ESplineCoordinateSpace::World);
				connectedRef->RerunConstructionScripts();
			}
		}
	}
}

void AAINode::SetReferences(AActor* node, AActor* spline)
{
	connectedReferences.Add(spline);
	nodeReferences.Add(node);
}

// Called every frame
void AAINode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

