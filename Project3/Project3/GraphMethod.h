#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

vector<int> BFS(Graph* graph, int vertex);
vector<int> DFS(Graph* graph, int vertex);
void DFS_R(Graph* graph, vector<bool>* visit, int vertex, vector<int>& visitOrder);
vector<int> DFS_R(Graph* graph, int vertex);
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);

#endif
#pragma once
