#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include <ext/slist>
#include "BulkPackets.h"
#include "BulkGraphEdge.h"
#include "BulkNode.h"
class BulkNode;
#include "BulkSession.h"
#include "BulkNetwork.h"
#include "RandomGenerator.h"
using namespace __gnu_cxx;
using namespace std;
class BulkSession;
class BulkLink:public BulkGraphEdge
{
	private:
		void _defaultInit();
	public:
		BulkLink():BulkGraphEdge() {}
		BulkLink(int from, int to);
		BulkLink(int from, int to, double weight, double capacity);
		BulkLink(BulkGraphEdge& edge);
		BulkSession* findSession(int sId);
		bool addSession(BulkSession& session);
		bool deleteSession(int sId);
		void pushHeadToTail(int numPackets, int sId);
		int  diffPackets(int sId);
		double getVaryCapacity();
		queue<BulkPackets>* getHead(int sId);
		queue<BulkPackets>* getTail(int sId);
		void setHeadPackets(int sId, int num, BulkPackets* packets = NULL);
		void setTailPackets(int sId, int num, BulkPackets* packets = NULL);
		void clearHeadPackets(int sId);
		void clearTailPackets(int sId);
		bool isUnderConstraints();
		~BulkLink(){};
	public:
		slist<BulkSession*>* session_;
		queue<BulkPackets>** head_;
		queue<BulkPackets>** tail_;
};
#endif
