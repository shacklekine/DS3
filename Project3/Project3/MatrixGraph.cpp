#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int* [size];
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int) * size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	// 유효한 vertex인지 확인
	if (vertex < 0 || vertex >= getSize()) {
		cout << "[ERROR] Invalid vertex: " << vertex << endl;
		return;
	}

	// 인접 행렬에서 vertex에 연결된 모든 엣지를 map에 추가
	for (int i = 0; i < getSize(); i++) {
		// vertex와 i번째 정점 사이에 엣지가 있고, i != vertex일 경우에만
		if (m_Mat[vertex][i] != 0 && i != vertex) {
			(*m)[i] = m_Mat[vertex][i];  // i번 정점으로의 엣지와 가중치를 m에 삽입
		}
	}
}


void MatrixGraph::insertEdge(int from, int to, int weight)
{
	// 인덱스가 유효한 범위 내에 있는지 확인
	if (from >= 0 && from < getSize() && to >= 0 && to < getSize())
	{
		// 엣지의 가중치를 인접 행렬에 삽입
		m_Mat[from][to] = weight;
	}
	else
	{
		// 인덱스가 유효하지 않다면 오류 처리 (선택 사항)
		cout << "[ERROR] Invalid edge: (" << from << ", " << to << ")" << endl;
	}
}

bool MatrixGraph::printGraph()
{
	if (m_Size < 0)
		return 0;

	cout << "Graph is MatrixGraph!" << endl;

	cout << '\t';
	for (int i = 0; i < m_Size; i++)
	{
		cout << "[" << i << "]" << '\t';
	}
	cout << endl;

	for (int i = 0; i < m_Size; i++)
	{
		cout << "[" << i << "]";
		for (int j = 0; j < m_Size && cout << '\t'; j++)
		{
			cout << m_Mat[i][j];
		}
		cout << endl;
	}
	return 1;
}

int** MatrixGraph::getMat() {
	return m_Mat;  // m_Mat는 인접 행렬을 가리킴
}