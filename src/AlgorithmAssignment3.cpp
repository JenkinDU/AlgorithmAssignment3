//============================================================================
// Name        : AlgorithmAssignment3.cpp
// Author      : Zhen Du
// Version     :
// Copyright   : No Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

#define FILE_PATH "./ProgrammingAssignment3SampleInput2.txt"
#define OUT_FILE_PATH "./ProgrammingAssignment3SampleOutput2.txt"
using namespace std;

long ttt = 0;
long st = 0;

long getCurrentTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

bool possible(int *A, int *P, int key, int index) {
	if (key < 0 || index < 0)
		return false;
	if(P[index] == key)
		return true;
	if (A[index] < key) {
		return false;
	} else if (A[index] == key) {
		return true;
	} else if (A[index] > key) {
		if (A[index - 1] > key) {
			if (possible(A, P, key - P[index], index - 1)) {
				return true;
			} else {
				return possible(A, P, key, index - 1);
			}
		} else if (A[index - 1] < key) {
			return possible(A, P, key - P[index], index - 1);
		} else if (A[index - 1] == key) {
			return true;
		}
	}
	return false;
}

void Merge(int *arrayA, int p, int q, int r) {
	int n0 = q - p + 1;
	int n1 = r - q;
	int *array0 = new int[n0];
	int *array1 = new int[n1];
	for (int i = 0; i < n0; i++) {
		array0[i] = arrayA[p + i];
	}
	for (int i = 0; i < n1; i++) {
		array1[i] = arrayA[q + 1 + i];
	}
	int m0 = 0;
	int m1 = 0;
	int j = 0;
	for (j = p; j <= r && m0 < n0 && m1 < n1; j++) {
		if (array0[m0] < array1[m1]) {
			arrayA[j] = array0[m0];
			m0++;
		} else {
			arrayA[j] = array1[m1];
			m1++;
		}
	}
	if (m0 == n0) {
		for (int i = 0; j <= r && i < n1 - m1; i++) {
			arrayA[j + i] = array1[m1 + i];
		}
	} else {
		for (int i = 0; j <= r && i < n0 - m0; i++) {
			arrayA[j + i] = array0[m0 + i];
		}
	}
	delete[] array0;
	delete[] array1;
}

void MergeSort(int *arrayA, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MergeSort(arrayA, p, q);
		MergeSort(arrayA, q + 1, r);
		Merge(arrayA, p, q, r);
	}
}

bool IsPossible(int key, std::vector<int>& v) {
	bool p = false;
	int size = static_cast<int>(v.size());
	int *A = new int[size];
	int *P = new int[size];
	for(vector<string>::size_type i = 0; i != v.size(); ++i) {
		P[i] = v[i];
	}
	MergeSort(P, 0, size-1);
	A[0] = P[0];
	for (int i = 1; i < size; i++) {
		A[i] = P[i] + A[i - 1];
	}
	for (int i = size - 1; i >= 0; i--) {
		if (P[i] > key) {
			continue;
		} else {
			p = possible(A, P, key, i);
			break;
		}
	}
	delete[] P;
	delete[] A;
	return p;
}

int stringToInt(char *str) {
	return atoi(str);
}

void SplitString(char *s, std::vector<int>& v,
		const char *c) {
	  char *p;
	  p = strtok(s, c);
	  while(p){
	    v.push_back(stringToInt(p));
	    p = strtok(NULL, c);
	  }
}

class Graph {
	int V;
	list<int> *adj;
	int fillOrder(int v, bool *visited);
public:
	Graph(int V);
	~Graph();
	void addEdge(int v, int w);
	vector<int> FindPotential();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int> [V];
}

Graph::~Graph() {
	delete[] adj;
}
void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

int Graph::fillOrder(int v, bool *visited) {
	visited[v] = true;
	int num = 0;
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i]) {
			num++;
			num += fillOrder(*i, visited);
		}
	return num;
}

vector<int> Graph::FindPotential() {
	vector<int> result;

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	for (int i = 0; i < V; i++)
		if (visited[i] == false) {

			int n = fillOrder(i, visited);

			result.push_back(n + 1);
		}
	delete[] visited;
	return result;
}

int main() {
	long start = getCurrentTime();
	ifstream fin(FILE_PATH);
	ofstream fout(OUT_FILE_PATH, ios::trunc);
	string s;

	while (!fin.eof()) {
		bool possible = false;
		std::getline(fin, s);
		string::size_type p = 0;
		string::size_type p1;
		string::size_type p2;
		string::size_type p3;
		string::size_type p4;
		string num;
		string x;
		string y;
		vector<int> numVec;
		vector<int> xVec;
		vector<int> yVec;

		p1 = s.find_first_of('{');
		if (p1 != string::npos) {
			num = s.substr(p, p1 - 2);
			p2 = s.find('}', p1);
			if (p2 != string::npos) {
				x = s.substr(p1 + 1, p2 - p1 - 1);
				p3 = p2 + 3;
				p4 = s.find('}', p3);
				if (p4 != string::npos) {
					y = s.substr(p3 + 1, p4 - p3 - 1);
				}
			}
		} else {
			continue;
		}
		if (!num.empty() && !x.empty() && !y.empty()) {
			const char *sep = ", ";
			const char *numc = num.c_str();
			char *numa = new char[num.length()+1];
			strcpy(numa, numc);
			const char *numd = numa;
			SplitString(numa, numVec, sep);
			const char *xc = x.c_str();
			char *xa = new char[x.length()+1];
			strcpy(xa, xc);
			const char *xd = xa;
			SplitString(xa, xVec, sep);
			const char *yc = y.c_str();
			char *ya = new char[y.length()+1];
			strcpy(ya, yc);
			SplitString(ya, yVec, sep);
			const char *yd = ya;
			delete[] numd;
			delete[] xd;
			delete[] yd;
			st = getCurrentTime();
			if (xVec.size() == yVec.size()) {
				vector<int> group;
				int total = numVec[0];
				int key = numVec[1];
				Graph g(total);
				for (vector<string>::size_type i = 0; i != xVec.size(); ++i) {
					int xsint = xVec[i];
					int ysint = yVec[i];
					g.addEdge(xsint, ysint);
					g.addEdge(ysint, xsint);
				}
				group = g.FindPotential();
				possible = IsPossible(key, group);
				ttt +=(getCurrentTime()-st);
			}

		}
		if (possible) {
			fout << "Possible" << endl;
		} else {
			fout << "Impossible" << endl;
		}
	}
	fout.close();
	fin.close();
	printf("Total time:%.4f\n", (getCurrentTime() - start) / 1000.0);
	printf("Waste time:%.4f", ttt/1000.0);
	return 0;
}
