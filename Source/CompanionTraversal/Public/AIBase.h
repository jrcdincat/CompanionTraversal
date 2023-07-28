// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AINode.h"
#include "AIEdge.h"
#include "AISplineGraph.h"
#include "AIBase.generated.h"

UCLASS()
class COMPANIONTRAVERSAL_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UFUNCTION(BlueprintCallable, Category = "Pathfinding"
	TArray<int32> RunDijkstra(TMap<int32, AAINode*>& graph, const int32 startNode, const int32 endNode);

	// Graph
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* graphActor = nullptr;
		//TMap<int32, AAINode*> Graph;
		
	// Run test through level blueprint Debug Key 'G'
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	TArray<int32> PathFindingTest(int32 startNode, int32 endNode);

	void PopulateTestGraph();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
