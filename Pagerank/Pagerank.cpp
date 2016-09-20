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

//P describes a probability matrix
class P {
private:
	vector<vector<double> > data;
public:
	vector<size_t> nE; //describes the number of outgoing edges from each vertex 
	vector<size_t> nE2; //describes the number of vertices to which each vertex does not have an edge

	size_t size() { return data.size(); }

	P(const matrix& m, double alpha = 0.85) {
		size_t nV = m.size();
		data = vector<vector<double> >(nV, vector<double>(nV, 0.0));
		//create nE and n2
		for (size_t i = 0; i < nV; ++i) {
			const auto& v = m[i];
			nE.push_back(v.size());
			size_t n = nV - 1;
			if (v.size() != 0) {
				size_t prev = m[i][0];
				--n;
				for (size_t j = 1; j < v.size(); ++j) {
					if (v[j] != prev)
						--n;
				}			
			} 
			nE2.push_back(n);
		}

		//create data
		for (size_t i = 0; i < size(); ++i) {
			size_t current = 0;
			size_t n1 = nE[i];
			size_t n2 = nE2[i];

			size_t prev = 0;
			for (const size_t& j : m[i]) {
				(n2 == 0) ? data[i][j] += 1.0 / n1 : data[i][j] += alpha / n1;
			}
			for (size_t j = 0; j < size(); ++j) {
				if (j != i) {
					if (m[i].size() == 0) { data[i][j] = 1.0 / n2; }
					else if (data[i][j] == 0) { data[i][j] = (1.0 - alpha) / n2; }
				}
			}
		}
	}

	vector<double> operator[](size_t index) {
		return data[index];
	}

	void print() {
		for (const auto& row : data)
		{
			for (const double& i : row) { cout << i << " "; } cout << endl;
		}
	}

};

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

//approximate eigenvector
/*
vector<int> approx_eig(const P& P) {
	size_t nV = P.size();
	vector<int> eig(nV, 1);

//method 1: approximate eigenvector by p_i = p_(i-1)P, i = 1..m
#ifdef METHOD_1

#endif

#ifdef METHOD_1

#endif

#ifdef METHOD_1

#endif

	return eig;
}
*/

void print_eig(vector<int> eig) {
	for (const int& i : eig) { cout << i << " "; } cout << endl;
}

int main()
{
	string filepath = "C:\\Users\\fawge\\Documents\\Visual Studio 2015\\Projects\\EDAN55lab4\\Data\\";
	string filename = "three.txt";

	string full_path = filepath + filename;
	matrix m = adjacency_matrix(full_path);

	//print_matrix(m);
	auto p = P(m);
	p.print();
    return 0;
}

