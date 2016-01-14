#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <ext/slist>
#include <string.h>
using namespace std;
using namespace __gnu_cxx;

class Graph  
{
	private:
		int n;	// number of vertices
		int e;	// number of edges, one edge counts two times, since later one edge has two opposite direction flow
		slist<GraphNode>* aList = null;	// adjacency lists
	public:
	Graph():n(0), e(0){}
	Graph(int _n);
	virtual ~Graph();
	int getVertices() const; //return the number of nodes
	int getEdges() const;	  //return the number of directed edges
	double capacity(int v1, int v2) const;	//return capcity of edge (v1, v2)
	double weight(int v1, int v2) const;	//return weight of edge (v1, v2)
	void putEdge(int v1, int v2, double weight, double capacity);		
	void removeEdge(int v1, int v2);
	void clearEdges();
	bool connected() const;
	void shortestPaths(int sourceVertex, double* distanceFromSource, int* predecessor) const;
	static Graph* importGraph(string cfilename);
	void exportGraph(string cfilename) const;
	static Graph* genRandomGraph(int numNodes, int numEdges, double minCapacity, double maxCapacity);

	//copy construct function
	Graph& operator=(const Graph &graph)
	{
		if (this != graph) {
			Graph graphTemp(graph);
			
			this->n = graphTemp.n;
			this->e = graphTemp.e;
			if (graphTemp.aList	!= null) {
				slist<GraphNode>* sTemp = graphTemp.aList;
				graphTemp.aList = this->aList;
				this->aList = sTemp;
			}
		}
		return *this;
	}

	Graph(const Graph& G)
	{
		this->n = G.n;
		this->e = G.e;
		this->aList = new slist<GraphNode>;
		
	}
};
#endif