#include <fstream>
#include <sstream>
#include <iostream>
#include <cfloat>
#include "Graph.h"
#include "BulkGraphNode.h"
#include "RandomGenerator.h"

Graph::Graph(int _n):n(_n)
{
	if (this->n < 0) {
		this->n = 0;
	}
	aList = new slist<GraphNode>[n+1];
	e = 0;
}

Graph::~Graph()
{
	delete [] aList;
	aList = NULL;
}

/**
 * @brief getVertices 
 * 获得节点的个数
 * @return {int}
 */
int Graph::getVertices() const
{
	return n;
}


/**
 * @brief getEdges 
 * 获得边的数量
 * @return {interge}
 */
int Graph::getEdges() const
{
	return e;
}

/**
 * @brief capacity 
 * 获得当前链路(v1, v2)的带宽
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {double}
 */
double Graph::capacity(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		GraphNode node(v2, 0, 0);

		slist<GraphNode>::iterator result = find(aList[v1].begin(), aList[v1].end(), node);

		if (result != aList[v1].end())  // edge (v1, v2) do exist
		{
			return (*result).capacity;
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

/** @return weight of an edge (v1, v2) */
double
Graph::weight(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		GraphNode node(v2, 0, 0);

		slist<GraphNode>::iterator result = find(aList[v1].begin(), aList[v1].end(), node);


		if (result != aList[v1].end())  // edge (v1, v2) do exist
		{
			return (*result).weight;
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

void Graph::putEdge(int v1, int v2, double weight, double capacity)
{	
	if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
		return;

	GraphNode node(v2, weight, capacity);

	slist<GraphNode>::iterator result = find(aList[v1].begin(), aList[v1].end(), node);

	if (result == aList[v1].end())  // new edge
	{
		// put v2 at front of chain aList[v1]
		aList[v1].push_front(node);
		
		e++;
	}
	/*else{
		//edge already exist, need to change weight, capacity???
	}*/
}

/** remove the edge (v1,v2) in the bidirected graph 
  * you need to call removeEdge(v1, v2) and removeEdge(v2, v1) to remove link v1-v2
  */
void
Graph::removeEdge(int v1, int v2)
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		GraphNode node(v2, 0, 0);

		slist<GraphNode>::iterator result = find(aList[v1].begin(), aList[v1].end(), node);


		if (result != aList[v1].end())  // edge (v1, v2) do exist
		{
			result = aList[v1].erase(result);
						
			// need to delete result ??????????
			e--;
		}
	}
}

void
Graph::clearEdges()
{
	//remove all the edges in the graph
	for(int i = 1; i <= n; i++)
		aList[i].clear();

	e = 0;
}

/** @return true iff bidirected graph is connected 
  * here it is treated as a undirected graph, it's called when we generate a connected random
  * graph
  */
bool
Graph::connected() const
{
	bool* reach = new bool [n + 1];
	
	for (int i = 1; i <= n; i++)
        	reach[i] = false;
        	
	// mark vertices reachable from vertex 1
	rDfs(1, reach);
      
	// check if all vertices marked
	for (int i = 1; i <= n; i++){
        	if (false == reach[i])
			return false;
	}
			
	delete [] reach;
	reach = NULL;
	return true;		
}

/** recursive dfs method
  * reach[i] is set to label for all vertices reachable
  * from vertex v */
void
Graph::rDfs(int v, bool* reach) const
{
	reach[v] = true;

	if(aList[v].empty())
		return;

	slist<GraphNode>::iterator iv = aList[v].previous(aList[v].end());

	while (true)
	{// visit an adjacent vertex of v
		int u = (*iv).id;
		if (false == reach[u])  // u is an unreached vertex
			rDfs(u, reach);

		if(iv == aList[v].begin())
			break;
		else
			iv = aList[v].previous(iv);
	}
}

/** Dijkstra's shortest-path algorithm */
void
Graph::shortestPaths(int sourceVertex, double* distanceFromSource, int* predecessor) const
{
	if (sourceVertex < 1 || sourceVertex > n)
	{
		cerr << "wrong source vertex " << sourceVertex << endl;
		return;
	}


	GraphNode node;

	slist<int> newReachableVertices;

	slist<GraphNode>::iterator result;

	// initialize
	for(int i = 1; i <= n; i++)
	{
		node.id = i;
		result = find(aList[sourceVertex].begin(), aList[sourceVertex].end(), node);

		if(result == aList[sourceVertex].end())
		{
			//sourceVertex and node i is NOT connected directly
			distanceFromSource[i] = DBL_MAX;
			predecessor[i] = -1;
		}else{
			//sourceVertex and node i is connected directly
			distanceFromSource[i] = (*result).weight;
			predecessor[i] = sourceVertex;
			newReachableVertices.push_front(i);
		}
	}

	//source vetex has no predecessor
	predecessor[sourceVertex] = 0;
	distanceFromSource[sourceVertex] = 0.0;

	while(!newReachableVertices.empty())
	{
		//more path exist
		//find unreached vertex v with least distanceFrom Source
		slist<int>::iterator iNewReachableVertices = newReachableVertices.previous(newReachableVertices.end());

		int v = *iNewReachableVertices;

		while(iNewReachableVertices != newReachableVertices.begin())
		{
			iNewReachableVertices = newReachableVertices.previous(iNewReachableVertices);
			int w = *iNewReachableVertices;
			if(distanceFromSource[w] < distanceFromSource[v])
				v = w;
		}

		//next shortest path is to vertex v
		//delete v from newReachableVertices and
		//update distanceFromSource
		iNewReachableVertices = find(newReachableVertices.begin(), newReachableVertices.end(), v);
		newReachableVertices.erase(iNewReachableVertices);

		for(int j = 1; j <= n; j++)
		{
			node.id = j;
			result = find(aList[v].begin(), aList[v].end(), node);

			if(result != aList[v].end() && (-1 == predecessor[j] || 
				distanceFromSource[j] > distanceFromSource[v] + (*result).weight)){

				//distanceFromSource[j] decreases
				distanceFromSource[j] = distanceFromSource[v] + (*result).weight;

				//add j to newReachablevertices
				if(-1 == predecessor[j])
					//not reached before
					newReachableVertices.push_front(j);

				predecessor[j] = v;
			}
		}

	}

}

/** Generate a connected random bidirected graph with nodes = n, E(edges) = m
  * the probability that v1 is connected with v2 is a Bernoulli Distribution(p)
  * p is numEdges / (n(n-1)/2) 
  * the weight of each edge is 1 +- epsilon, epsilon is between [0.0, 0.01)
  * Here we assume each link is bidirected. The weights of the two directions are same, but 
  * capacity is different
  */
Graph*
Graph::genRandomGraph(int numNodes, int numEdges, double minCapacity, double maxCapacity)
{
	int i, j;
	int connected;
	
	//# times failed to create a connected graph
	int failedtimes; 		
	double p;
	double epsilon;
	int isPositive;
	//the probability that epsilon is positive is 0.5
	double isPositiveProb = 0.5; 

	double default_weight = 1.0;

	double capacity = 1.0;

	Graph* g = new Graph(numNodes);

	p = 2.0 * ((double) numEdges / (double) (numNodes * (numNodes - 1))); 

	failedtimes = 0;
	while(true)
	{
		for(i = 1; i <= numNodes; i++)
		{
			for(j = i + 1; j <= numNodes; j++)
			{
				connected = RandomGenerator::genBernoulliInt(p);
				if(1 == connected){
					epsilon = RandomGenerator::genUniform() / 100.0;
					isPositive = RandomGenerator::genBernoulliInt(isPositiveProb);
					if(1 == isPositive){
						capacity = RandomGenerator::genUniformDouble(minCapacity, maxCapacity);
						g->putEdge(i, j, default_weight + epsilon, capacity);
						//cout << "Edge " << i << "-" << j << " (" << default_weight - epsilon << ")" << endl;

						capacity = RandomGenerator::genUniformDouble(minCapacity, maxCapacity);
						g->putEdge(j, i, default_weight + epsilon, capacity);
						//cout << "Edge " << j << "-" << i << " (" << default_weight - epsilon << ")" << endl;

					}else{
						capacity = RandomGenerator::genUniformDouble(minCapacity, maxCapacity);
						g->putEdge(i, j, default_weight - epsilon, capacity);
						//cout << "Edge " << i << "-" << j << " (" << default_weight + epsilon << ")" << endl;

						capacity = RandomGenerator::genUniformDouble(minCapacity, maxCapacity);
						g->putEdge(j, i, default_weight - epsilon, capacity);
							//cout << "Edge " << j << "-" << i << " (" << default_weight + epsilon << ")" << endl;
					}
				}
			}
		}

		if(!g->connected()){
			//remove all the  edges
			g->clearEdges();
			cout << "Graph is not connected. All edges are cleared" << endl;
			failedtimes++;
			if(failedtimes >= 50)
			// I guess the edge/nodes ratio is too small to get a connected graph
				return NULL;
		}else{
			break;
		}
	}

	return g;
}

Graph*
Graph::importGraph(string cfilename)
{
	//ifstream inFile = ifstream(cfilename.data());
	ifstream inFile;
	inFile.open(cfilename.data(), ifstream::in);

	string inputLine;
	int lpos, rpos;
 
	Graph* g = NULL;
	int numNodes, numEdges, idx1, idx2;
	double weight, capacity;

	/*
	double epsilon;
	int isPositive;
	*/

	/* t number
		(total number of nodes)
	 */
	getline(inFile, inputLine);
	lpos = inputLine.find(" ");
	numNodes = atoi((inputLine.substr(lpos + 1)).data());
	g = new Graph(numNodes);

	/* T number
		(total number of links)
	 */
	getline(inFile, inputLine);
	lpos = inputLine.find(" ");
	numEdges = atoi((inputLine.substr(lpos + 1)).data());

	for(int i = 0; i < numNodes; i++)
	{
		// ? node_index name
		// Don't need to use those info. of nodes, just read and ignore it
		getline(inFile, inputLine);
	}

	for(int i = 0; i < numEdges; i++)
	{
		/* l linkidx n_idx1 n_idx2 weight
			l - unidirectional
		 */	
		getline(inFile, inputLine);
		lpos = inputLine.find(" ");
		lpos = inputLine.find(" ", lpos + 1);
		rpos = inputLine.find(" ", lpos + 1);
		idx1 = atoi((inputLine.substr(lpos + 1, rpos - lpos)).data());

		lpos = rpos;
		rpos = inputLine.find(" ", lpos + 1);
		idx2 = atoi((inputLine.substr(lpos + 1, rpos - lpos)).data());

		lpos = rpos;
		rpos = inputLine.find(" ", lpos + 1);
		weight = atof((inputLine.substr(lpos + 1, rpos - lpos)).data());

		/*
		epsilon = RandomGenerator::genUniform() / 100.0;
		isPositive = RandomGenerator::genBernoulliInt(0.5);
		if(1 == isPositive)
			weight = 1.0 + epsilon;
		else
			weight = 1.0 - epsilon;
		*/
	
		lpos = rpos;
		capacity = atof((inputLine.substr(lpos + 1)).data());
		//capacity *= 1e+;

		g->putEdge(idx1, idx2, weight, capacity);
	}

	inFile.close();

	return g;
}

void
Graph::exportGraph(string cfilename) const
{
	ofstream outFile;
	
	outFile.open(cfilename.data());

	/* t number
		(total number of nodes)
	   T number
		(total number of links)
	 */
	outFile << "t " << n <<	endl; 
	outFile << "T " << e << endl; 

	// ? node_index name
	
	int i;
	int numLinks;

	for(i = 1; i <= n; i++)
		outFile << "? " << i << " " << i << endl;

	slist<GraphNode>::iterator result;

	/* l linkidx n_idx1 n_idx2 weight
		l - unidirectional
	 */	
	for(i = 1, numLinks = 0; i <= n; i++)
	{
		if(!aList[i].empty())
		{
			result = aList[i].previous(aList[i].end());

			while(true)
			{	
				outFile << "L " << numLinks << " " << i << " " << (*result).id << " " << (*result).weight << " " << (*result).capacity << endl;
				numLinks++;
				
				if(result == aList[i].begin())
					break;
				result = aList[i].previous(result);
			}
		}
	}

	outFile.close();
}
