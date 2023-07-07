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

TArray<int32> AAIBase::RunPathFinding(TMap<int32, Node>& graph, int32 startNode, int32 targetNode)
{
	TMap<int32, float> distances;
	TMap<int32, int32> previous; 
	TQueue<int32> queue; 
	TArray<int32> visited; 


	// Initialize the graph distances and prevoius values
	for (auto& node : graph)
	{
		int32 id = node.Key; 
		distances.Add(id, TNumericLimits<float>::Max());
		previous.Add(id, -1);
	}


	distances[startNode] = 0;
	queue.Enqueue(startNode); // Tracking based on node id

	while (!queue.IsEmpty())
	{
		int32 currentId; 
		
		// currentID passed in as output parameter
		queue.Dequeue(currentId);
		visited.Add(currentId);

		if (currentId == targetNode)
		{
			break; 
		}

		Node& currentNode = graph[currentId];
		 
		for (auto& neighbor : currentNode._neighbors)
		{
			int32 neighborId = neighbor.Key;
			float weight = neighbor.Value;
			float newDistance = distances[currentId] + weight;

			// Update distance if path is shorter
			if (newDistance < distances[neighborId])
			{
				distances[neighborId] = newDistance;
				previous[neighborId] = currentId;;
				queue.Enqueue(neighborId);
			}
		}
	}


	TArray<int32> shortestPath; 
	int32 currentId = targetNode; 
	while (currentId != -1)
	{
		shortestPath.Insert(currentId, 0);
		currentId = previous[currentId];
	}

	return shortestPath;

	// Each spline references the Graph it lives in. 
	// List of all Unvisited nodes.
	// List of all distances (weights)

	// Mark the current node we are in as visited in the unvisited nodes list.
	// Update distances for adjacent nodes.

	// Select the node that is closest to the source node based on current known distances.
	// Mark node as visited (unvisited list) and add it to path.

	// Again check adjacent nodes, update any that didn't aleady have distance updated.
	// Distance calculated by adding weights of all edges that form the shortest path.

}


TArray<int32> AAIBase::RunDijkstra(TMap<int32, Node>& graph, const int32 startNode, const int32 endNode)
{ 
	TMap<int32, float> distances; 
	TMap<int32, int32> previousNodes; 
	TQueue<int32> queue; 
	TArray<int32> visited; 

	for (auto& node : graph)
	{
		int32 id = node.Key;
		distances.Add(id, TNumericLimits<float>::Max()); // Set to infinity
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

		Node& currentNode = graph[currentNodeID];

		for (auto& neighbor : graph[currentNodeID]._neighbors)
		{
			int32 neighborId = neighbor.Key;
			float neighborWeight = neighbor.Value;
			float newDistance = distances[currentNodeID] + neighborWeight;

			// Set to the lowest distance required to get to the neighbor node
			if (newDistance < distances[neighborId])
			{
				distances[neighborId] = newDistance;

				// Set it so that the previous node shows the current node since it is the shorter path
				previousNodes[neighborId] = currentNodeID;
				queue.Enqueue(neighborId);
			}
		}
	}

	TArray<int32> shortestPath;
	int32 currentNodeId = endNode;
	while (currentNodeId != -1)
	{
		shortestPath.Add(currentNodeId);
		currentNodeId = previousNodes[currentNodeId];
	}

	if (shortestPath.Num() > 0)
	{
		return shortestPath;
	}


	return shortestPath;
}

TArray<int32> AAIBase::PathFindingTest(int32 startNode, int32 endNode)
{
	PopulateTestGraph();
	return RunDijkstra(Graph, startNode, endNode);;
}

void AAIBase::PopulateTestGraph()
{
	Node node0;
	node0._id = 0;
	node0._neighbors.Add(1, 2.0f);
	node0._neighbors.Add(2, 6.0f);
	Graph.Add(0, node0);

	Node node1;
	node1._id = 1;
	node1._neighbors.Add(0, 2.0f);
	node1._neighbors.Add(3, 5.0f);
	Graph.Add(1, node1);

	Node node2;
	node2._id = 2;
	node2._neighbors.Add(0, 6.0f);
	node2._neighbors.Add(3, 8.0f);
	Graph.Add(2, node2);

	Node node3;
	node3._id = 3;
	node3._neighbors.Add(1, 5.0f);
	node3._neighbors.Add(2, 8.0f);
	node3._neighbors.Add(5, 15.0f);
	node3._neighbors.Add(4, 10.0f);
	Graph.Add(3, node3);

	Node node4;
	node4._id = 4;
	node4._neighbors.Add(3, 10.0f);
	node4._neighbors.Add(5, 6.0f);
	node4._neighbors.Add(6, 2.0f);
	Graph.Add(4, node4);

	Node node5;
	node5._id = 5;
	node5._neighbors.Add(3, 15.0f);
	node5._neighbors.Add(4, 6.0f);
	node5._neighbors.Add(6, 6.0f);
	Graph.Add(5, node5);

	Node node6;
	node6._id = 6;
	node6._neighbors.Add(4, 2.0f);
	node6._neighbors.Add(5, 6.0f);
	Graph.Add(6, node6);
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

