#include "GraphMethod.h"

std::vector<int> BFS(Graph* graph, int vertex)
{
    // 방문 여부를 저장하는 배열 (boolean 타입 사용)
    bool* visited = new bool[graph->getSize()];
    for (int i = 0; i < graph->getSize(); ++i) {
        visited[i] = false;  // 처음에는 모두 미방문 상태
    }

    // BFS를 위한 큐 초기화
    std::queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    // BFS 탐색을 수행하며 방문한 정점을 저장
    std::vector<int> visitOrder;  // 방문한 정점 순서 저장
    visitOrder.push_back(vertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        // 해당 정점에 인접한 정점들을 탐색
        map<int, int> adjEdges;
        graph->getAdjacentEdges(currentVertex, &adjEdges);

        // 인접한 정점들 중 방문하지 않은 정점들을 큐에 삽입
        for (auto it = adjEdges.begin(); it != adjEdges.end(); ++it) {
            if (!visited[it->first]) {
                visited[it->first] = true;
                q.push(it->first);
                visitOrder.push_back(it->first);
            }
        }
    }

    // 결과로 방문한 정점들의 순서를 반환
    delete[] visited;
    return visitOrder;  // 방문한 정점들의 순서를 반환
}

// DFS (비재귀적)
vector<int> DFS(Graph* graph, int vertex) {
    int size = graph->getSize();
    vector<int> visited(size, false);  // 방문 여부 추적
    vector<int> visitOrder;  // 방문 순서 기록
    stack<int> s;

    s.push(vertex);  // 시작 vertex를 스택에 넣음
    visited[vertex] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        visitOrder.push_back(current);  // 방문한 노드를 visitOrder에 기록

        // 인접한 노드를 스택에 넣음
        map<int, int> neighbors;
        graph->getAdjacentEdges(current, &neighbors);

        for (auto& neighbor : neighbors) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                s.push(neighbor.first);
            }
        }
    }

    return visitOrder;  // 방문 순서 반환
}

// DFS_R (재귀적)
void DFS_R(Graph* graph, vector<bool>* visit, int vertex, vector<int>& visitOrder) {
    (*visit)[vertex] = true;
    visitOrder.push_back(vertex);  // 방문한 노드를 visitOrder에 기록

    map<int, int> neighbors;
    graph->getAdjacentEdges(vertex, &neighbors);

    for (auto& neighbor : neighbors) {
        if (!(*visit)[neighbor.first]) {
            DFS_R(graph, visit, neighbor.first, visitOrder);  // 재귀 호출
        }
    }
}

vector<int> DFS_R(Graph* graph, int vertex) {
    vector<bool> visited(graph->getSize(), false);  // 방문 여부 추적
    vector<int> visitOrder;  // 방문 순서 기록

    DFS_R(graph, &visited, vertex, visitOrder);  // DFS_R 수행

    return visitOrder;  // 방문 순서 반환
}

bool Kruskal(Graph* graph)
{
	return true;
}

bool Dijkstra(Graph* graph, int vertex)
{
	return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{
	return true;
}

bool FLOYD(Graph* graph)
{
	return true;
}