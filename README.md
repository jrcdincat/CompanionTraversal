# AI Companion Traversal
This project is inspired by the Companion Traversal talk at GDC 2023 by Salaar Kohari at Santa Monica Studios. It is being developed in **_Unreal Engine 5.2_**. 
[Development updates will be posted on my website.](https://conradjonathan.com/ai-companion-traversal/)

The goal of this project is to develop a spline based traversal system that an AI companion or enemies can utilize. On this traversal system, a Companion can either lead 
or follow the player. It will utilize **_Dijkstra's Algorithm_** for pathing decisions. Level designers will be able to select the next and previous location on the path 
and the correct animation state. Each spline path will also contain a filter for what type of actor can travel on the path. This will be used to demonstrate how an enemy 
can traverse a section, but the filter prevents them from traversing another area that a companion and player can. The weights on each spline will update when an enemy 
traverses on it to ensure that the AI stays spread out rather than clumped. 

![image](https://github.com/jrcdincat/CompanionTraversal/assets/43223838/863209a0-dc0a-40a5-9557-d136fae9981e)
