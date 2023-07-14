// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "AINode.generated.h"

UCLASS()
class COMPANIONTRAVERSAL_API AAINode : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAINode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Construction")
		void SetSplinePointLocations();

	void SetReferences(AActor* node, AActor* spline);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 _id;
	TMap<int32, float> _neighbors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AActor> splineBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<AActor*, AActor*> nodeToSplineMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<AActor*, AActor*> referenceNodeToSplineMap;

	AActor* a;
};
