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
	// ��ȿ�� vertex���� Ȯ��
	if (vertex < 0 || vertex >= getSize()) {
		cout << "[ERROR] Invalid vertex: " << vertex << endl;
		return;
	}

	// ���� ��Ŀ��� vertex�� ����� ��� ������ map�� �߰�
	for (int i = 0; i < getSize(); i++) {
		// vertex�� i��° ���� ���̿� ������ �ְ�, i != vertex�� ��쿡��
		if (m_Mat[vertex][i] != 0 && i != vertex) {
			(*m)[i] = m_Mat[vertex][i];  // i�� ���������� ������ ����ġ�� m�� ����
		}
	}
}


void MatrixGraph::insertEdge(int from, int to, int weight)
{
	// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
	if (from >= 0 && from < getSize() && to >= 0 && to < getSize())
	{
		// ������ ����ġ�� ���� ��Ŀ� ����
		m_Mat[from][to] = weight;
	}
	else
	{
		// �ε����� ��ȿ���� �ʴٸ� ���� ó�� (���� ����)
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
	return m_Mat;  // m_Mat�� ���� ����� ����Ŵ
}