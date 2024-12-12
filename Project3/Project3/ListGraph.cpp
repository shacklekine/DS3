#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	// ��ȿ�� vertex���� Ȯ��
	if (vertex < 0 || vertex >= getSize()) {
		cout << "[ERROR] Invalid vertex: " << vertex << endl;
		return;
	}

	// �ش� vertex�� ���� ����Ʈ�� �����ͼ� m�� ����
	*m = m_List[vertex];
}

void ListGraph::insertEdge(int from, int to, int weight)
{

		m_List[from][to] = weight;

}


bool ListGraph::printGraph()
{
	cout << "Graph is ListGraph!" << endl;

	for (int i = 0; i < m_Size; i++)
	{
		cout << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && cout << " -> "; it_++)
		{
			cout << "(" << it_->first << "," << it_->second << ")";
		}
		cout << endl;
	}
	cout << endl;
	return 1;
}