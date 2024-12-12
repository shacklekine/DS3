#ifndef _MANAGER_H_
#define _MANAGER_H_
#define _CRT_SECURE_NO_WARNINGS

#include "GraphMethod.h"
#include <iostream>  // 표준 입출력
#include <fstream>   // 파일 입출력
#include <string>    // std::string 및 stoi 함수
#include <cctype>    // isdigit 함수
class Manager {
private:
	Graph* graph;
	ofstream fout;
	int load;


public:
	Manager();
	~Manager();

	void run(const char* command_txt);

	bool LOAD(char* filename);
	bool PRINT();

	bool mBFS(int vertex);
	bool mDFS_R(int vertex);
	bool mDFS(int vertex);
	bool mDIJKSTRA(int vertex);
	bool mKRUSKAL();
	bool mBELLMANFORD(int s_vertex, int e_vertex);
	bool mFLOYD();

	void printErrorCode(int n);
};

#endif