// Pagerank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#define ALPHA (0.85)

using namespace std;

typedef vector<vector<size_t> > matrix;

matrix adjacency_matrix(const string& filename) {
	ifstream ifs(filename);
	size_t nV;
	string line = "";
	getline(ifs, line);
	istringstream is(line);
	is >> nV;

	matrix matrix(nV);
	while (getline(ifs, line)) {
		istringstream iss(line);
		size_t u, v;
		while (iss >> u >> v) {
			matrix[u].push_back(v);
		}
	}


	return matrix;
}

void print_matrix(const matrix& matrix) {
	for (size_t r = 0; r < matrix.size(); ++r)
	{
		vector<size_t> row = matrix[r];
		for (const size_t& i : row)
		{
			cout << r << " " << i << "\t";
		}
		cout << endl;
	}
	
}

vector<size_t> Random_Surfer_Sim(const matrix& m, const string& filename) {
	vector<size_t> pagerank(m.size(), 0);
	size_t nItr = 0;
	cout << "Enter number of iterations for file " + filename + ": ";
	cin >> nItr;
	if (nItr <= 0) { 
		cout << "number of iterations must be larger than 0" << endl;
	}
	size_t currPage = 0;
	++pagerank[currPage];
	for (size_t i = 0; i < nItr; ++i) {
		if (rand() % 100 < ALPHA) {
			//go to random connected page
			size_t nConnections = m[currPage].size();
			size_t randConnection = rand() % nConnections;
			size_t nextPage = m[currPage][randConnection];
			currPage = nextPage;
		}
		else {
			//go to random page
			size_t nConnections = m.size();
			size_t nextPage = rand() % nConnections;
			currPage = nextPage;
		}
		++pagerank[currPage];
	}
	return pagerank;
}

int main()
{
	string filepath = "C:\\Users\\biz\\Documents\\Visual Studio 2015\\Projects\\PageRank\\Data\\";
	string filename = "three.txt";

	string full_path = filepath + filename;
	matrix m = adjacency_matrix(full_path);

	//pagerank by random surfer simulation
	vector<size_t> pagerank = Random_Surfer_Sim(m, filename);


	//print_matrix(m);
    return 0;
}

