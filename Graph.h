// Graph.h: interface for the Graph class.
//
//////////////////////////////////////////////////////////////////////

#include <ext/slist>
#include <string.h>

using namespace std;
using namespace __gnu_cxx;

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

//supporting data structure, used by some sorting, comparison algorithms
class GraphEdge
{
/* edge used to caculate the flow, (v1, v2) and (v2, v1) is the link with
 * opposite flow direction
 */

public:
	int v1;		//node id of the origin
	int v2;		//node id of the end
	int numPacketHead; //edge边头的队列
	int numPacketTail; //edge边尾的队列

public:
	//constructors
	GraphEdge():numPacketHead(0), numPacketTail(0)
	{
	}

	GraphEdge(int _v1, int _v2)
	:v1(_v1), v2(_v2), numPacketHead(0), numPacketTail(0)
	{
	}

	//destructor
	virtual ~GraphEdge()
	{}

	bool operator == (const GraphEdge& edge)
	{
		return (v1 == edge.v1) && (v2 == edge.v2);
	}

	/**
	 * @brief addNumPacketHead 
	 * 边头部增加拥塞数据块
	 * @param {integer} numPackets 
	 * @param {boolean} isAdd 是否进行加减
	 * @return true
	 */
	bool addNumPacketHead(bool isAdd, int numPackets = 1)
	{
		if (isAdd) {
			this->numPacketHead = this->numPacketHead + numPackets;
		} else {
			this->numPacketHead = this->numPacketHead - numPackets;
		}
		return true;
	}

	/**
	 * @brief addNumPacketTail 
	 * 边尾部增加拥塞数据块
	 * @param {integer} numPackets
	 * @param {boolean} isAdd 是否进行加减
	 * @return true
	 */
	bool addNumPacketTail(bool isAdd, int numPackets = 1)
	{
		if (isAdd) {
			this->numPacketTail = this->numPacketTail + numPackets;
		} else {
			this->numPacketTail = this->numPacketTail - numPackets;
		}
		return true;
	}
};

struct ltedge
{
	bool operator()(const GraphEdge edge1, const GraphEdge edge2) const
	{
		if(edge1.v1 < edge2.v1)
			return true;

		if(edge1.v1 > edge2.v1)
			return false;

		if(edge1.v2 < edge2.v2)
			return true;

		return false;
	}
};

//components in the linked adjacent list representation of a digraph
class GraphNode
{
public:
	int id;				    //id of the end node of the edge
	int numHeadQueue;       //number of the head queues
	int numTailQueue;       //number of the tail queues
	double weight;			//weight of the edge, used to compute the shoretest path
	double capacity;		//capacity of the edge

public:
	//constructors
	GraphNode():numHeadQueue(0), numTailQueue(0)
	{}

	GraphNode(int _id, double _weight, double _capacity)
		:id(_id), weight(_weight), capacity(_capacity), numHeadQueue(0), numTailQueue(0)
	{}
	
	//destructor
	virtual ~GraphNode()
	{}

	bool operator == (const GraphNode& node)
	{
		return id == node.id;
	}

	/**
	 * @brief getNumHeadQueue 
	 * 获得该节点中的head queues的数量
	 * @return {integer}
	 */
	int getNumHeadQueue()
	{
		return this->numHeadQueue;
	}

	/**
	 * @brief getNumTailQueue 
	 * 获得该节点中的tail queues的数量
	 * @return {integer}
	 */
	int getNumTailQueue()
	{
		return this->numTailQueue;
	}

	/**
	 * @brief operator++ 
	 * 后缀++操作符(用于numTailQueue的计数++)
	 * @return 
	 */
	GraphNode& operator++(int)
	{
		this->numTailQueue++;
		return *this;
	}

	/**
	 * @brief operator++ 
	 * 前缀++操作符(用于numHeadQueue的计数++)
	 * @return 
	 */
	GraphNode& operator++()
	{
		++this->numHeadQueue;
		return *this;
	}

	/**
	 * @brief operator-- 
	 * 后缀++操作符(用于numTailQueue的计数--)
	 * @return 
	 */
	GraphNode& operator--(int)
	{
		this->numTailQueue--;
		return *this;
	}

	/**
	 * @brief operator-- 
	 * 前缀--操作符(用于numHeadQueue的计数--)
	 * @return 
	 */
	GraphNode& operator--()
	{
		--this->numHeadQueue;
		return *this;
	}
};

/** linked adjacency list representation of a digraph */
class Graph  
{
public:
	int n;							// number of vertices
	int e = 0;							// number of edges, one edge counts two times, since later one edge has two opposite direction flow
	slist<GraphNode>* aList = null;		// adjacency lists
   
private:
	//recursive dfs method
	void rDfs(int v, bool* reach) const;

public:
	//constructor
	Graph(int _n);

	//destructor
	virtual ~Graph();

	int vertices() const;					//return the number of nodes
	int edges() const;					    //return the number of directed edges

	double capacity(int v1, int v2) const;			//return capcity of edge (v1, v2)
	double weight(int v1, int v2) const;			//return weight of edge (v1, v2)

	//put the edge (v1,v2) into the bidirected graph
	void putEdge(int v1, int v2, double weight, double capacity);		
	//remove the edge (v1,v2) from the bidirected graph
	void removeEdge(int v1, int v2);
	//remove all edges
	void clearEdges();

	//return true iff bidirected graph is connected 
	bool connected() const;
	//Dijkstra's shortest-path algorithm
	void shortestPaths(int sourceVertex, double* distanceFromSource, int* predecessor) const;

	//import the graph from file cfilename
	static Graph* importGraph(string cfilename);
	//export the graph to file cfilename
	void exportGraph(string cfilename) const;
	
	//Generate a connected random bidirected graph
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
};
