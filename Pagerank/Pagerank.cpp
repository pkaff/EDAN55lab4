// Pagerank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#define METHOD_1
//#define METHOD_2
//#define METHOD_3

using namespace std;

//adjacency matrix
typedef vector<vector<size_t> > matrix;

//probability matrix
typedef vector<vector<double> > P;

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

void print_P(const P& P) {
	for (const auto& row : P)
	{
		for (const double& i : row) { cout << i << " "; } cout << endl;
	}
}

//get probability matrix from adjacency matrix
P get_P(const matrix& m, double alpha = 0.85, bool sparse = true) {
	size_t nV = m.size();
	P P(nV);
	for (auto col : m) {
		size_t current = 0;
		for (size_t i = 0; i < nV; ++i) {
			int pr = 0;
			if (col[i]) {

			}
		}
	}
	return P;
}

//approximate eigenvector
vector<int> approx_eig(const P& P, vector<int> eig0 = vector<int>()) {
	size_t nV = P.size();
	if (eig0.size == 0) { eig0 = vector<int>(nV, 1); }

//method 1: approximate eigenvector by p_i = p_(i-1)P, i = 1..m
#ifdef METHOD_1

#endif

#ifdef METHOD_1

#endif

#ifdef METHOD_1

#endif

	return eig0;
}

void print_eig(vector<int> eig) {
	for (const int& i : eig) { cout << i << " "; } cout << endl;
}

int main()
{
	string filepath = "C:\\Users\\biu\\Documents\\Visual Studio 2015\\Projects\\PageRank\\Data\\";
	string filename = "three.txt";

	string full_path = filepath + filename;
	matrix m = adjacency_matrix(full_path);

	print_matrix(m);
    return 0;
}

