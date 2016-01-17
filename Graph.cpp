#include "Graph.h"
Graph::Graph(int _n):n(_n)
{
	if (this->n < 0) {
		this->n = 0;
	}
	aList = new BulkGraphNode[n+1];
	this->e = 0;
}

Graph::~Graph()
{
	delete [] aList;
	aList = NULL;
}

/**
 * @brief getVertices 
 * 获得节点的个数
 * @return {interge}
 */
int Graph::getVertices() const
{
	return this->n;
}


/**
 * @brief getEdges 
 * 获得边的数量
 * @return {interge}
 */
int Graph::getEdges() const
{
	return this->e;
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
		BulkGraphEdge edge(v1, v2);
		BulkGraphEdge* nowEdge = aList[v1].getBulkEdge(&edge);
		if (nowEdge != NULL) {
			return nowEdge->getCapacity();
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

/**
 * @brief weight 
 * 返回两点之间的权值
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {boolean}
 */
double Graph::weight(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		BulkGraphEdge edge(v1, v2);
		BulkGraphEdge* nowEdge = aList[v1].getBulkEdge(&edge);
		if (nowEdge != NULL) {
			return nowEdge->getWeight();
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

/**
 * @brief putEdge 
 * 图中增加边，以及权值，带宽
 * @param {interge} v1
 * @param {interge} v2
 * @param {double} weight
 * @param {double} capacity
 */
void Graph::putEdge(int v1, int v2, double weight, double capacity)
{	
	if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
		return;
	}
	BulkGraphNode node1(v1);
	if (aList[v1].getNodeId() == -1) {
		aList[v1] = node1;
	}
	BulkGraphNode node2(v2);
	if (aList[v2].getNodeId() == -1) {
		aList[v2] = node2;
	}
	BulkGraphEdge edge(v1, v2, weight, capacity);
	aList[v1].addBulkEdge(&edge);
	aList[v2].addBulkEdge(&edge);
	this->e++
}

/**
 * @brief removeEdge 
 * 图中删除边，以及权值，带宽
 * @param {interge} v1
 * @param {interge} v2
 */
void Graph::removeEdge(int v1, int v2)
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n) {
		if (aList[v1].getNodeId() == -1 || 
			aList[v2].getNodeId() == -1) {
			return;
		} else {
			BulkGraphEdge edge(v1, v2);
			if (aList[v1].removeBulkEdge(&edge) || 
				aList[v2].removeBulkEdge(&edge)) {
				this->e--;
			}
		}
	}
}

/**
 * @brief clearEdges 
 * 删除所有边
 */
void Graph::clearEdges()
{
	delete[] aList;
	this->e = 0;
}

/**
 * @brief connected 
 * 判断两点之间是否连通
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {boolean} 
 */
bool Graph::connected(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n) {
		if (aList[v1].getNodeId() == -1 ||
			aList[v2].getNodeId() == -1) {
			return false;
		} else {
			int* visited = (int*)malloc(this->n + 1);
			if (!visited[v1]) {
				this->_dfsVisit(v1, visited);
			}
		}
		if (visited[v2]) {
			return true;
		}
	}
	return false;
}

/**
 * @brief _dfsVisit 
 * 深度优先搜索算法
 * @param {interge} uSource 
 * @param {interge[]} visited (存放已经访问过的节点id) 
 * @param {interge} vSink (存放已经访问过的节点id) 
 */
void Graph::_dfsVisit(int uSource, int* visited, int vSink)
{
	visited[u] = 1;
	slist<BulkGraphEdge>* headEdge = aList[u].getHeadEdge();
	slist<BulkGraphEdge>::iterator iter = headEdge->begin();
	slist<BulkGraphEdge>::iterator iterEnd = headEdge->end();
	for (; iter < iterEnd; iter++) {
		if (visited[vSink]) {
			break;
		}
		int sink = iter->getGraphEdgeSink();
		if (!visited[sink] && sink != vSink) {
			this->_dfsVisit(sink, visited, vSink);
		} else {
			visited[sink] = 1;
			break;
		}
	}
}

/**
 * @brief importGraph 
 * 导入网路拓朴结构
 * @param {文件名} cfilename
 *
 * @return 
 */
Graph* Graph::importGraph(string cfilename)
{
	//ifstream inFile = ifstream(cfilename.data());
	ifstream inFile;
	inFile.open(cfilename.data(), ifstream::in);

	string inputLine;
	int lpos, rpos;
 
	Graph* g = NULL;
	int numNodes, numEdges, idx1, idx2;
	double weight, capacity;

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
