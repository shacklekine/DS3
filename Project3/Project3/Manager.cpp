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
        // 명령어가 "LOAD"라면 LOAD 함수 호출
        if (strncmp(buf, "LOAD", 4) == 0) {
            char filename[100];
            sscanf(buf + 5, "%s", filename);  // "LOAD <filename>" 형식에서 filename 추출
            if (!LOAD(filename)) {
                printErrorCode(100);  // 오류 코드 출력
            }
        }
        // 다른 명령어 처리 로직 추가 가능
        else if (strncmp(buf, "PRINT", 5) == 0) {
            if (!PRINT()) {
                printErrorCode(200);  // 오류 코드 출력
            }
        }
        // 명령어가 "BFS"라면 BFS 함수 호출
        else if (strncmp(buf, "BFS", 3) == 0) {
            int vertex;
            sscanf(buf + 4, "%d", &vertex);  // "BFS <vertex>" 형식에서 vertex 추출
            if (!mBFS(vertex)) {
                printErrorCode(300);  // 오류 코드 출력
            }
        }
        // 명령어가 "DFS"라면 DFS 함수 호출
        else if (strncmp(buf, "DFS", 3) == 0 && (buf[3] == ' ' || buf[3] == '\0')) {
            int vertex;
            sscanf(buf + 4, "%d", &vertex);  // "DFS <vertex>" 형식에서 vertex 추출
            if (!mDFS(vertex)) {
                printErrorCode(400);  // 오류 코드 출력
            }
        }
        // 명령어가 "DFS_R"이라면 DFS Recursive 함수 호출
        else if (strncmp(buf, "DFS_R", 5) == 0 && (buf[5] == ' ' || buf[5] == '\0')) {
            int vertex;
            sscanf(buf + 6, "%d", &vertex);  // "DFS_R <vertex>" 형식에서 vertex 추출
            if (!mDFS_R(vertex)) {
                printErrorCode(500);  // 오류 코드 출력
            }
        }
        // 명령어가 "DIJKSTRA"라면 Dijkstra 알고리즘 함수 호출
        else if (strncmp(buf, "DIJKSTRA", 8) == 0) {
            int vertex;
            sscanf(buf + 9, "%d", &vertex);  // "DIJKSTRA <vertex>" 형식에서 vertex 추출
            if (!mDIJKSTRA(vertex)) {
                printErrorCode(600);  // 오류 코드 출력
            }
        }
        // 명령어가 "KRUSKAL"이라면 Kruskal 알고리즘 함수 호출
        else if (strncmp(buf, "KRUSKAL", 7) == 0) {
            if (!mKRUSKAL()) {
                printErrorCode(700);  // 오류 코드 출력
            }
        }
        // 명령어가 "BELLMANFORD"라면 Bellman-Ford 알고리즘 함수 호출
        else if (strncmp(buf, "BELLMANFORD", 11) == 0) {
            int s_vertex, e_vertex;
            sscanf(buf + 12, "%d %d", &s_vertex, &e_vertex);  // "BELLMANFORD <start_vertex> <end_vertex>"
            if (!mBELLMANFORD(s_vertex, e_vertex)) {
                printErrorCode(800);  // 오류 코드 출력
            }
        }
        // 명령어가 "FLOYD"라면 Floyd-Warshall 알고리즘 함수 호출
        else if (strncmp(buf, "FLOYD", 5) == 0) {
            if (!mFLOYD()) {
                printErrorCode(900);  // 오류 코드 출력
            }
        }
        else if (strncmp(buf, "EXIT", 4) == 0) {
            fout << "======== EXIT ========" << endl;
            fout << "Success" << endl;
            fout << "=====================" << endl;  // 로그 끝

            break;
        }
        // 기타 명령어 처리
        else {
            fout << "[ERROR] Unknown command: " << buf << endl;
        }
    }
    fin.close();
}

bool Manager::LOAD(char* filename)
{
    fout << "======== LOAD ========" << endl; // LOAD 시작 출력

    // 파일 열기
    ifstream fin(filename);
    if (!fin)
    {
        printErrorCode(100);  // 오류 코드 출력
        
        return false;
    }


    char graphType;
    int graphSize;

    // 첫 번째 줄에서 그래프 타입과 크기 읽기
    fin >> graphType >> graphSize;

    // 기존 그래프 정보 삭제
    if (graph != nullptr)
    {
        delete graph;
    }

    // 그래프 타입에 맞게 새로 생성
    if (graphType == 'L') // List 형식
    {
        graph = new ListGraph(0, graphSize);
    }
    else if (graphType == 'M') // Matrix 형식
    {
        graph = new MatrixGraph(1, graphSize);
    }
    else
    {
        printErrorCode(100);

        fin.close();
        return false;
    }

    // 엣지 정보 읽기
    int from, to, weight;
    int row = 0;  // 행 번호 (vertex)
    string line;
    vector<int> dataCount;  // 각 줄의 인자 갯수를 저장할 배열

    // 'L'일 때만 인자 개수를 세기 위해서 처리
    if (graphType == 'L')
    {

        // 첫 번째 줄을 제외한 나머지 줄을 읽어 인자 개수를 기록
        while (getline(fin, line))
        {

            int count = 0;
            // 공백을 기준으로 인자 개수 세기
            for (char c : line)
            {
                if (isspace(c))
                {
                    count++;
                }
            }
            // 인자 갯수는 count + 1 (공백으로 구분된 항목 수)
            dataCount.push_back(count + 1);
        }
 
        // 파일을 처음부터 다시 읽기 위해 포인터를 처음으로 되돌림
        fin.clear();
        fin.seekg(0);

        // 첫 번째 줄 (그래프 타입, 크기) 다시 읽기
        fin >> graphType >> graphSize;

        string line;
        int from, to, weight;
        int index = 1;  // dataCount 배열의 인덱스

        // 한 줄씩 읽어서 처리
        while (fin && index < dataCount.size())
        {
            if (dataCount[index] == 1)  // 인자 1개 (from)
            {
                if (fin >> from)
                {
                    index++;  // 다음 줄로 넘어갈 때 인덱스 증가
                    continue;
                }
            }
            else if (dataCount[index] == 2)  // 인자 2개 (from, to)
            {
                if (fin >> to >> weight)
                {
                    static_cast<ListGraph*>(graph)->insertEdge(from, to, weight);  // weight는 0으로 처리

                    index++;  // 다음 줄로 넘어갈 때 인덱스 증가
                    continue;
                }
            }

        }
    }


    // 만약 MatrixGraph 타입일 경우
    else if (graphType == 'M')
    {
        // 그래프 행렬을 채우기
        while (fin && row < graphSize)
        {
            for (int col = 0; col < graphSize; ++col)
            {
                fin >> weight;  // 각 위치의 가중치를 읽음
                static_cast<MatrixGraph*>(graph)->insertEdge(row, col, weight);
            }
            ++row;  // 한 행을 처리한 후 다음 행으로
        }
    }

    // 그래프 로드 성공
    fout << "Success" << endl;
    fout << "=====================" << endl;  // 로그 끝

    fin.close();
    return true;
}




bool Manager::PRINT()
{
    // 그래프가 nullptr인 경우 오류 처리
    if (graph == nullptr) {
        return false;
    }

    // 그래프가 ListGraph 타입인지 확인하고, 그 경우에만 출력
    if (graph->getType() == 0) {
        graph->printGraph();
        fout << "======== PRINT ========" << endl; //  출력
        ListGraph* listGraph = static_cast<ListGraph*>(graph); // ListGraph로 캐스팅
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
        fout << "=====================" << endl;  // 로그 끝
        return true;
    }
    // 그래프가 MatrixGraph 타입일 경우
    else if (graph->getType() == 1) {
        // MatrixGraph의 출력

 
        graph->printGraph();
        fout << "======== PRINT ========" << endl; //  출력
        MatrixGraph* matrixGraph = static_cast<MatrixGraph*>(graph); // MatrixGraph로 캐스팅

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
        fout << "=====================" << endl;  // 로그 끝
    }

    return true;
}

bool Manager::mBFS(int vertex)
{
    // 그래프가 nullptr인 경우 오류 처리
    if (graph == nullptr) {
        fout << "[ERROR] Graph is not initialized!" << std::endl;
        return false;
    }

    // 유효한 vertex인지 확인
    if (vertex < 0 || vertex >= graph->getSize()) {
        fout << "[ERROR] Invalid vertex: " << vertex << std::endl;
        return false;
    }

    // 출력 형식 시작
    fout << "======== BFS ========" << std::endl;
    fout << "startvertex: " << vertex << std::endl;

    // BFS를 수행하고, 방문하는 정점들의 결과를 받아옴
    std::vector<int> visitOrder = BFS(graph, vertex);

    // 방문한 정점들의 순서를 출력
    for (size_t i = 0; i < visitOrder.size(); ++i) {
        if (i != 0) {
            fout << " -> ";  // 첫 번째 정점은 "->" 붙이지 않음
        }
        fout << visitOrder[i];
    }
    fout << std::endl;

    fout << "=====================" << std::endl;
    return true;
}

// DFS 함수 호출 및 결과 출력
bool Manager::mDFS(int vertex) {
    if (vertex >= graph->getSize()) {
        printErrorCode(400);  // 유효하지 않은 vertex 오류 처리
        return false;
    }

    vector<int> visitOrder = DFS(graph, vertex);  // DFS 수행하여 방문 순서 얻기

    ofstream fout("log.txt", ios::app);
    if (!fout) {
        cerr << "[ERROR] log file open error!" << endl;
        return false;
    }

    fout << "======== DFS ========" << endl;
    fout << "startvertex: " << vertex << endl;
    for (int v : visitOrder) {
        fout << v << " -> ";  // 방문한 노드 출력
    }
    fout.seekp(-4, ios::cur); // 마지막 " -> " 제거
    fout << endl;
    fout << "=====================" << endl;

    return true;
}

// DFS_R 함수 호출 및 결과 출력
bool Manager::mDFS_R(int vertex) {
    if (vertex >= graph->getSize()) {
        printErrorCode(400);  // 유효하지 않은 vertex 오류 처리
        return false;
    }

    vector<int> visitOrder = DFS_R(graph, vertex);  // DFS_R 수행하여 방문 순서 얻기

    ofstream fout("log.txt", ios::app);
    if (!fout) {
        cerr << "[ERROR] log file open error!" << endl;
        return false;
    }

    fout << "======== DFS_R ========" << endl;
    fout << "startvertex: " << vertex << endl;
    for (int v : visitOrder) {
        fout << v << " -> ";  // 방문한 노드 출력
    }
    fout.seekp(-4, ios::cur); // 마지막 " -> " 제거
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
