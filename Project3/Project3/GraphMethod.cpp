#include "GraphMethod.h"

std::vector<int> BFS(Graph* graph, int vertex)
{
    // �湮 ���θ� �����ϴ� �迭 (boolean Ÿ�� ���)
    bool* visited = new bool[graph->getSize()];
    for (int i = 0; i < graph->getSize(); ++i) {
        visited[i] = false;  // ó������ ��� �̹湮 ����
    }

    // BFS�� ���� ť �ʱ�ȭ
    std::queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    // BFS Ž���� �����ϸ� �湮�� ������ ����
    std::vector<int> visitOrder;  // �湮�� ���� ���� ����
    visitOrder.push_back(vertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        // �ش� ������ ������ �������� Ž��
        map<int, int> adjEdges;
        graph->getAdjacentEdges(currentVertex, &adjEdges);

        // ������ ������ �� �湮���� ���� �������� ť�� ����
        for (auto it = adjEdges.begin(); it != adjEdges.end(); ++it) {
            if (!visited[it->first]) {
                visited[it->first] = true;
                q.push(it->first);
                visitOrder.push_back(it->first);
            }
        }
    }

    // ����� �湮�� �������� ������ ��ȯ
    delete[] visited;
    return visitOrder;  // �湮�� �������� ������ ��ȯ
}

// DFS (�������)
vector<int> DFS(Graph* graph, int vertex) {
    int size = graph->getSize();
    vector<int> visited(size, false);  // �湮 ���� ����
    vector<int> visitOrder;  // �湮 ���� ���
    stack<int> s;

    s.push(vertex);  // ���� vertex�� ���ÿ� ����
    visited[vertex] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        visitOrder.push_back(current);  // �湮�� ��带 visitOrder�� ���

        // ������ ��带 ���ÿ� ����
        map<int, int> neighbors;
        graph->getAdjacentEdges(current, &neighbors);

        for (auto& neighbor : neighbors) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                s.push(neighbor.first);
            }
        }
    }

    return visitOrder;  // �湮 ���� ��ȯ
}

// DFS_R (�����)
void DFS_R(Graph* graph, vector<bool>* visit, int vertex, vector<int>& visitOrder) {
    (*visit)[vertex] = true;
    visitOrder.push_back(vertex);  // �湮�� ��带 visitOrder�� ���

    map<int, int> neighbors;
    graph->getAdjacentEdges(vertex, &neighbors);

    for (auto& neighbor : neighbors) {
        if (!(*visit)[neighbor.first]) {
            DFS_R(graph, visit, neighbor.first, visitOrder);  // ��� ȣ��
        }
    }
}

vector<int> DFS_R(Graph* graph, int vertex) {
    vector<bool> visited(graph->getSize(), false);  // �湮 ���� ����
    vector<int> visitOrder;  // �湮 ���� ���

    DFS_R(graph, &visited, vertex, visitOrder);  // DFS_R ����

    return visitOrder;  // �湮 ���� ��ȯ
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