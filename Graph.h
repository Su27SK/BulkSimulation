#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <ext/slist>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cfloat>
#include "BulkGraphNode.h"
#include "BulkGraphEdge.h"
#include "RandomGenerator.h"
using namespace std;
using namespace __gnu_cxx;

class Graph  
{
	private:
		int n;	// number of vertices
		int e;	// number of edges, one edge counts two times, since later one edge has two opposite direction flow
		BulkGraphNode* aList; // adjacency lists
		void _dfsVisit(int uSource, int* visited, int vSink); //DFS algorithm
	public:
		Graph():n(0), e(0){}
		Graph(int _n);
		virtual ~Graph();
		int getVertices() const; //return the number of nodes
		int getEdges() const; //return the number of directed edges
		double capacity(int v1, int v2) const; //return capcity of edge (v1, v2)
		double weight(int v1, int v2) const; //return weight of edge (v1, v2)
		void putEdge(int v1, int v2, double weight, double capacity);		
		void removeEdge(int v1, int v2);
		void clearEdges();
		bool connected(int v1, int v2) const;
		static Graph* importGraph(string cfilename);
		void exportGraph(string cfilename) const;
};
#endif
