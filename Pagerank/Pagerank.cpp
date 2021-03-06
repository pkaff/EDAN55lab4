// Pagerank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

#define ALPHA (0.85)
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

	P(P& other) : data(other.data), nE(other.nE), nE2(other.nE2) { }

	P(const matrix& m, double alpha = ALPHA) {
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

	vector<double> mul(vector<double>& v) {
		vector<double> tmp;
		for (size_t j = 0; j < size(); ++j) {
			double res = 0.0;
			for (size_t i = 0; i < size(); ++i)
				res += v[i] * data[i][j];
			tmp.push_back(res);
		}
		return tmp;
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

vector<double> approx_eig_nontrivial(matrix& m, size_t itr = 10000) {
	size_t nV = m.size();
	vector<double> p(nV, 0.0);
	p[0] = 1.0;
	vector<double> D;
	for (auto& v : m) {
		if (v.size() > 0) {
			D.push_back(0);
		} else {
			D.push_back(1.0 / nV);
		}
	}

	for (size_t i = 0; i < itr; ++i) {
		vector<double> temp(nV, 0.0);
		double sum = 0.0;
		for (size_t j = 0; j < nV; ++j) {
			for (auto& k : m[j])
				temp[k] += ALPHA*p[j] / m[j].size();
			sum += ALPHA*p[j] * D[j] + p[j]*(1.0 - ALPHA) / nV;
		}
		for (size_t j = 0; j < nV; ++j) {
			temp[j] += sum;
		}
		p = temp;
	}
	return p;
}

//approximate eigenvector
vector<double> approx_eig(P& P, size_t itr = 100) {
	const size_t nV = P.size();
	cout << nV << endl;
	vector<double> eig(nV, 1.0);

	//method 1: approximate eigenvector by p_i = p_(i-1)P, i = 1..m
#ifdef METHOD_1
	for (size_t i = 0; i < itr; ++i) {
		eig = P.mul(eig);
	}
#endif

#ifdef METHOD_2

#endif

#ifdef METHOD_3

#endif

	return eig;
}

void print_eig(vector<double> eig) {
	for (const double& i : eig) { cout << i << " "; } cout << endl;
}

vector<pair<size_t, size_t> > Random_Surfer_Sim(const matrix& m, const string& filename, int& nItr) {
	vector<pair<size_t, size_t> > pagerank(m.size());
	for (size_t i = 0; i < pagerank.size(); ++i) {
		pagerank[i] = make_pair(i, 0);
	}
	cout << "Enter number of iterations for file " + filename + ": ";
	cin >> nItr;
	if (nItr <= 0) { 
		cout << "Number of iterations must be larger than 0" << endl;
	}
	size_t currPage = 0;
	pagerank[currPage].second++;
	for (size_t i = 0; i < nItr; ++i) {
		size_t nextPage;
		if (m[currPage].size() == 0) {
			//go to random page
			size_t nConnections = m.size();
			nextPage = rand() % nConnections;
		} else if (rand() % 100 < ALPHA*100) {
			//go to random connected page
			size_t nConnections = m[currPage].size();
			size_t randConnection = rand() % nConnections;
			nextPage = m[currPage][randConnection];
		}
		else {
			//go to random page
			size_t nConnections = m.size();
			nextPage = rand() % nConnections;
		}
		currPage = nextPage;
		pagerank[currPage].second++;
	}
	return pagerank;
}

void printPagerank(vector<pair<size_t, size_t> >& pagerank, const string& filepath, const string& filename, int nItr) {
	sort(pagerank.begin(), pagerank.end(), [](pair<size_t, size_t>& p1, pair<size_t, size_t>& p2) { return p1.second > p2.second; });
	ofstream ofs(filepath + "output\\" + filename);
	ofs << filename;
	for (size_t i = 0; i < min((size_t)5, pagerank.size()); ++i) {
		double percent = 0;
		if (nItr != 0) {
			percent = (pagerank[i].second / (double)nItr) * 100;
		}
		ofs << "\t" << pagerank[i].first << " (" << percent << "%)";
	}
	ofs << endl;
}

int main()
{
	string filepath = "C:\\Users\\biz\\Documents\\Visual Studio 2015\\Projects\\PageRank\\Data\\";
	vector<string> filenames;
	filenames.push_back("three.txt");
	filenames.push_back("tiny.txt");
	filenames.push_back("medium.txt");
	filenames.push_back("wikipedia.txt");
	filenames.push_back("p2p-Gnutella08-mod.txt");

	for (const string& filename : filenames) {
		matrix m = adjacency_matrix(filepath + "input\\" + filename);

		//Pagerank by linalg
		//vector<double> e = approx_eig_nontrivial(m);
		//print_eig(e);

		//pagerank by random surfer simulation
		int nItr;
		vector<pair<size_t, size_t> > pagerank = Random_Surfer_Sim(m, filename, nItr);
		printPagerank(pagerank, filepath, filename, nItr);
		}
    return 0;
}

