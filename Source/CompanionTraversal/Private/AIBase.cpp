// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<int32> AAIBase::RunDijkstra(TMap<int32, AAINode*>& graph, const int32 startNode, const int32 endNode)
{ 
	TMap<int32, float> distances; 
	TMap<int32, int32> previousNodes; 
	TQueue<int32> queue; 
	TArray<int32> visited; 

	for (auto& node : graph)
	{
		int32 id = node.Key;
		distances.Add(id, TNumericLimits<float>::Max());
		previousNodes.Add(id, -1); // Set to undefined 
	}

	// Set start node
	queue.Enqueue(startNode);
	distances[startNode] = 0;

	while (!queue.IsEmpty())
	{
		int32 currentNodeID;
		queue.Dequeue(currentNodeID);
		visited.Add(currentNodeID);

		if (currentNodeID == endNode)
		{
			break;
		}

		AAINode& currentNode = *graph[currentNodeID];
		for (auto& neighbor : graph[currentNodeID]->_neighbors)
		{
			int32 neighborId = neighbor.Key;
			float neighborWeight = neighbor.Value;
			float newDistance = distances[currentNodeID] + neighborWeight;
			//FString str = FString::Printf(TEXT("New: %f"), newDistance);
			//str.Append(FString::Printf(TEXT(" wD: %f"), distances[neighborId]));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, str);

			// Set to the lowest distance required to get to the neighbor node
			if (newDistance < distances[neighborId])
			{
				distances[neighborId] = newDistance;

				// Set previous node as current since the current node is a shorter distance
				previousNodes[neighborId] = currentNodeID;
				queue.Enqueue(neighborId);
			}
		}
	}

	// Adds the nodes in reverse order, based on previous nodes as they store the node that is the shortest distance away on the path
	TArray<int32> shortestPath;
	int32 currentNodeId = endNode;
	while (currentNodeId != -1)
	{
		shortestPath.Add(currentNodeId);
		currentNodeId = previousNodes[currentNodeId];
	}

	Algo::Reverse(shortestPath); // Reverse array to be in order from start to end

	return shortestPath;
}

TArray<int32> AAIBase::PathFinding(int32 startNode, int32 endNode)
{
	//Graph.Empty();
	//PopulateTestGraph();
	TArray<int32> shortestPath;

	if (IsValid(graphActor))
	{
		TMap<int32, AAINode*>& Graph = Cast<AAISplineGraph>(graphActor)->Graph;
		shortestPath = RunDijkstra(Graph, startNode, endNode);
	}
	

	//for (auto& node : Graph)
	//{
	//	node.Value->Destroy();
	//}

	return shortestPath;
}

void AAIBase::PopulateTestGraph()
{
	//AAINode* node0 = GetWorld()->SpawnActor<AAINode>();
	//node0->_id = 0;
	//node0->_neighbors.Add(1, 2.0f);
	//node0->_neighbors.Add(2, 6.0f);
	//Graph.Add(0, node0);

	//AAINode* node1 = GetWorld()->SpawnActor<AAINode>();
	//node1->_id = 1;
	//node1->_neighbors.Add(0, 2.0f);
	//node1->_neighbors.Add(3, 5.0f);
	//Graph.Add(1, node1);

	//AAINode* node2 = GetWorld()->SpawnActor<AAINode>();
	//node2->_id = 2;
	//node2->_neighbors.Add(0, 6.0f);
	//node2->_neighbors.Add(3, 8.0f);
	//Graph.Add(2, node2);

	//AAINode* node3 = GetWorld()->SpawnActor<AAINode>();
	//node3->_id = 3;
	//node3->_neighbors.Add(1, 5.0f);
	//node3->_neighbors.Add(2, 8.0f);
	//node3->_neighbors.Add(5, 15.0f);
	//node3->_neighbors.Add(4, 10.0f);
	//Graph.Add(3, node3);

	//AAINode* node4 = GetWorld()->SpawnActor<AAINode>();
	//node4->_id = 4;
	//node4->_neighbors.Add(3, 10.0f);
	//node4->_neighbors.Add(5, 6.0f);
	//node4->_neighbors.Add(6, 2.0f);
	//Graph.Add(4, node4);

	//AAINode* node5 = GetWorld()->SpawnActor<AAINode>();
	//node5->_id = 5;
	//node5->_neighbors.Add(3, 15.0f);
	//node5->_neighbors.Add(4, 6.0f);
	//node5->_neighbors.Add(6, 6.0f);
	//Graph.Add(5, node5);

	//AAINode* node6 = GetWorld()->SpawnActor<AAINode>();
	//node6->_id = 6;
	//node6->_neighbors.Add(4, 2.0f);
	//node6->_neighbors.Add(5, 6.0f);
	//Graph.Add(6, node6);
}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
