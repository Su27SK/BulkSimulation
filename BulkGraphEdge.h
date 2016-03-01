#ifndef _BULKGRAPHEDGE_H_
#define _BULKGRAPHEDGE_H_
class BulkGraphEdge
{
	private:
		int _v1;		   //node id of the origin
		int _v2;		   //node id of the end
		double _weight;	   //(数学期望)
		double _capacity;  //链路带宽
	public:
		BulkGraphEdge():_v1(-1), _v2(-1), _weight(0.0), _capacity(0.0){}
		BulkGraphEdge(int v1, int v2, double weight = 0.0, double capacity = 0.0);
		BulkGraphEdge(const BulkGraphEdge& edge);
		BulkGraphEdge(BulkGraphEdge& edge);
		bool operator == (const BulkGraphEdge& edge);
		BulkGraphEdge& setWeight(double weight);
		BulkGraphEdge& setCapacity(double capacity);
		int getGraphEdgeSource() const;
		int getGraphEdgeSink() const;
		double getWeight() const;
		double getCapacity() const;
		virtual ~BulkGraphEdge(){}
};

#endif
