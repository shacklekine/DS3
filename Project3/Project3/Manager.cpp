#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if (load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt) {
    ifstream fin;
    fin.open(command_txt);

    if (!fin) {
        fout << "[ERROR] command file open error!" << endl;
        return;
    }

    char buf[129] = { 0 };

    while (fin.getline(buf, 128)) {
        // ��ɾ "LOAD"��� LOAD �Լ� ȣ��
        if (strncmp(buf, "LOAD", 4) == 0) {
            char filename[100];
            sscanf(buf + 5, "%s", filename);  // "LOAD <filename>" ���Ŀ��� filename ����
            if (!LOAD(filename)) {
                printErrorCode(100);  // ���� �ڵ� ���
            }
        }
        // �ٸ� ��ɾ� ó�� ���� �߰� ����
        else if (strncmp(buf, "PRINT", 5) == 0) {
            if (!PRINT()) {
                printErrorCode(200);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "BFS"��� BFS �Լ� ȣ��
        else if (strncmp(buf, "BFS", 3) == 0) {
            int vertex;
            sscanf(buf + 4, "%d", &vertex);  // "BFS <vertex>" ���Ŀ��� vertex ����
            if (!mBFS(vertex)) {
                printErrorCode(300);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "DFS"��� DFS �Լ� ȣ��
        else if (strncmp(buf, "DFS", 3) == 0 && (buf[3] == ' ' || buf[3] == '\0')) {
            int vertex;
            sscanf(buf + 4, "%d", &vertex);  // "DFS <vertex>" ���Ŀ��� vertex ����
            if (!mDFS(vertex)) {
                printErrorCode(400);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "DFS_R"�̶�� DFS Recursive �Լ� ȣ��
        else if (strncmp(buf, "DFS_R", 5) == 0 && (buf[5] == ' ' || buf[5] == '\0')) {
            int vertex;
            sscanf(buf + 6, "%d", &vertex);  // "DFS_R <vertex>" ���Ŀ��� vertex ����
            if (!mDFS_R(vertex)) {
                printErrorCode(500);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "DIJKSTRA"��� Dijkstra �˰��� �Լ� ȣ��
        else if (strncmp(buf, "DIJKSTRA", 8) == 0) {
            int vertex;
            sscanf(buf + 9, "%d", &vertex);  // "DIJKSTRA <vertex>" ���Ŀ��� vertex ����
            if (!mDIJKSTRA(vertex)) {
                printErrorCode(600);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "KRUSKAL"�̶�� Kruskal �˰��� �Լ� ȣ��
        else if (strncmp(buf, "KRUSKAL", 7) == 0) {
            if (!mKRUSKAL()) {
                printErrorCode(700);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "BELLMANFORD"��� Bellman-Ford �˰��� �Լ� ȣ��
        else if (strncmp(buf, "BELLMANFORD", 11) == 0) {
            int s_vertex, e_vertex;
            sscanf(buf + 12, "%d %d", &s_vertex, &e_vertex);  // "BELLMANFORD <start_vertex> <end_vertex>"
            if (!mBELLMANFORD(s_vertex, e_vertex)) {
                printErrorCode(800);  // ���� �ڵ� ���
            }
        }
        // ��ɾ "FLOYD"��� Floyd-Warshall �˰��� �Լ� ȣ��
        else if (strncmp(buf, "FLOYD", 5) == 0) {
            if (!mFLOYD()) {
                printErrorCode(900);  // ���� �ڵ� ���
            }
        }
        else if (strncmp(buf, "EXIT", 4) == 0) {
            fout << "======== EXIT ========" << endl;
            fout << "Success" << endl;
            fout << "=====================" << endl;  // �α� ��

            break;
        }
        // ��Ÿ ��ɾ� ó��
        else {
            fout << "[ERROR] Unknown command: " << buf << endl;
        }
    }
    fin.close();
}

bool Manager::LOAD(char* filename)
{
    fout << "======== LOAD ========" << endl; // LOAD ���� ���

    // ���� ����
    ifstream fin(filename);
    if (!fin)
    {
        printErrorCode(100);  // ���� �ڵ� ���
        
        return false;
    }


    char graphType;
    int graphSize;

    // ù ��° �ٿ��� �׷��� Ÿ�԰� ũ�� �б�
    fin >> graphType >> graphSize;

    // ���� �׷��� ���� ����
    if (graph != nullptr)
    {
        delete graph;
    }

    // �׷��� Ÿ�Կ� �°� ���� ����
    if (graphType == 'L') // List ����
    {
        graph = new ListGraph(0, graphSize);
    }
    else if (graphType == 'M') // Matrix ����
    {
        graph = new MatrixGraph(1, graphSize);
    }
    else
    {
        printErrorCode(100);

        fin.close();
        return false;
    }

    // ���� ���� �б�
    int from, to, weight;
    int row = 0;  // �� ��ȣ (vertex)
    string line;
    vector<int> dataCount;  // �� ���� ���� ������ ������ �迭

    // 'L'�� ���� ���� ������ ���� ���ؼ� ó��
    if (graphType == 'L')
    {

        // ù ��° ���� ������ ������ ���� �о� ���� ������ ���
        while (getline(fin, line))
        {

            int count = 0;
            // ������ �������� ���� ���� ����
            for (char c : line)
            {
                if (isspace(c))
                {
                    count++;
                }
            }
            // ���� ������ count + 1 (�������� ���е� �׸� ��)
            dataCount.push_back(count + 1);
        }
 
        // ������ ó������ �ٽ� �б� ���� �����͸� ó������ �ǵ���
        fin.clear();
        fin.seekg(0);

        // ù ��° �� (�׷��� Ÿ��, ũ��) �ٽ� �б�
        fin >> graphType >> graphSize;

        string line;
        int from, to, weight;
        int index = 1;  // dataCount �迭�� �ε���

        // �� �پ� �о ó��
        while (fin && index < dataCount.size())
        {
            if (dataCount[index] == 1)  // ���� 1�� (from)
            {
                if (fin >> from)
                {
                    index++;  // ���� �ٷ� �Ѿ �� �ε��� ����
                    continue;
                }
            }
            else if (dataCount[index] == 2)  // ���� 2�� (from, to)
            {
                if (fin >> to >> weight)
                {
                    static_cast<ListGraph*>(graph)->insertEdge(from, to, weight);  // weight�� 0���� ó��

                    index++;  // ���� �ٷ� �Ѿ �� �ε��� ����
                    continue;
                }
            }

        }
    }


    // ���� MatrixGraph Ÿ���� ���
    else if (graphType == 'M')
    {
        // �׷��� ����� ä���
        while (fin && row < graphSize)
        {
            for (int col = 0; col < graphSize; ++col)
            {
                fin >> weight;  // �� ��ġ�� ����ġ�� ����
                static_cast<MatrixGraph*>(graph)->insertEdge(row, col, weight);
            }
            ++row;  // �� ���� ó���� �� ���� ������
        }
    }

    // �׷��� �ε� ����
    fout << "Success" << endl;
    fout << "=====================" << endl;  // �α� ��

    fin.close();
    return true;
}




bool Manager::PRINT()
{
    // �׷����� nullptr�� ��� ���� ó��
    if (graph == nullptr) {
        return false;
    }

    // �׷����� ListGraph Ÿ������ Ȯ���ϰ�, �� ��쿡�� ���
    if (graph->getType() == 0) {
        graph->printGraph();
        fout << "======== PRINT ========" << endl; //  ���
        ListGraph* listGraph = static_cast<ListGraph*>(graph); // ListGraph�� ĳ����
        for (int i = 0; i < listGraph->getSize(); ++i) {
            fout << "[" << i << "]";
            map<int, int> adjEdges;
            listGraph->getAdjacentEdges(i, &adjEdges);

            for (auto it = adjEdges.begin(); it != adjEdges.end(); ++it) {
                fout << " -> (" << it->first << "," << it->second << ")";
            }
            fout << endl;
        }
        fout << endl;
        fout << "=====================" << endl;  // �α� ��
        return true;
    }
    // �׷����� MatrixGraph Ÿ���� ���
    else if (graph->getType() == 1) {
        // MatrixGraph�� ���

 
        graph->printGraph();
        fout << "======== PRINT ========" << endl; //  ���
        MatrixGraph* matrixGraph = static_cast<MatrixGraph*>(graph); // MatrixGraph�� ĳ����

        fout << '\t';
        for (int i = 0; i < matrixGraph->getSize(); i++) {
            fout << "[" << i << "]" << '\t';
        }
        fout << endl;

        for (int i = 0; i < matrixGraph->getSize(); i++) {
            fout << "[" << i << "]";
            for (int j = 0; j < matrixGraph->getSize() && fout << '\t'; j++) {
                fout << matrixGraph->getMat()[i][j];
            }
            fout << endl;
        }
        fout << endl;
        fout << "=====================" << endl;  // �α� ��
    }

    return true;
}

bool Manager::mBFS(int vertex)
{
    // �׷����� nullptr�� ��� ���� ó��
    if (graph == nullptr) {
        fout << "[ERROR] Graph is not initialized!" << std::endl;
        return false;
    }

    // ��ȿ�� vertex���� Ȯ��
    if (vertex < 0 || vertex >= graph->getSize()) {
        fout << "[ERROR] Invalid vertex: " << vertex << std::endl;
        return false;
    }

    // ��� ���� ����
    fout << "======== BFS ========" << std::endl;
    fout << "startvertex: " << vertex << std::endl;

    // BFS�� �����ϰ�, �湮�ϴ� �������� ����� �޾ƿ�
    std::vector<int> visitOrder = BFS(graph, vertex);

    // �湮�� �������� ������ ���
    for (size_t i = 0; i < visitOrder.size(); ++i) {
        if (i != 0) {
            fout << " -> ";  // ù ��° ������ "->" ������ ����
        }
        fout << visitOrder[i];
    }
    fout << std::endl;

    fout << "=====================" << std::endl;
    return true;
}

// DFS �Լ� ȣ�� �� ��� ���
bool Manager::mDFS(int vertex) {
    if (vertex >= graph->getSize()) {
        printErrorCode(400);  // ��ȿ���� ���� vertex ���� ó��
        return false;
    }

    vector<int> visitOrder = DFS(graph, vertex);  // DFS �����Ͽ� �湮 ���� ���

    ofstream fout("log.txt", ios::app);
    if (!fout) {
        cerr << "[ERROR] log file open error!" << endl;
        return false;
    }

    fout << "======== DFS ========" << endl;
    fout << "startvertex: " << vertex << endl;
    for (int v : visitOrder) {
        fout << v << " -> ";  // �湮�� ��� ���
    }
    fout.seekp(-4, ios::cur); // ������ " -> " ����
    fout << endl;
    fout << "=====================" << endl;

    return true;
}

// DFS_R �Լ� ȣ�� �� ��� ���
bool Manager::mDFS_R(int vertex) {
    if (vertex >= graph->getSize()) {
        printErrorCode(400);  // ��ȿ���� ���� vertex ���� ó��
        return false;
    }

    vector<int> visitOrder = DFS_R(graph, vertex);  // DFS_R �����Ͽ� �湮 ���� ���

    ofstream fout("log.txt", ios::app);
    if (!fout) {
        cerr << "[ERROR] log file open error!" << endl;
        return false;
    }

    fout << "======== DFS_R ========" << endl;
    fout << "startvertex: " << vertex << endl;
    for (int v : visitOrder) {
        fout << v << " -> ";  // �湮�� ��� ���
    }
    fout.seekp(-4, ios::cur); // ������ " -> " ����
    fout << endl;
    fout << "=====================" << endl;

    return true;
}

bool Manager::mDIJKSTRA(int vertex)
{
    return true;
}

bool Manager::mKRUSKAL()
{
    return true;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
    return true;
}

bool Manager::mFLOYD()
{
    return true;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}
