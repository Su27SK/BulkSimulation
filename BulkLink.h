#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include <ext/slist>
#include "BulkGraphEdge.h"
#include "BulkNode.h"
class BulkNode;
#include "BulkSession.h"
#include "BulkNetwork.h"
using namespace __gnu_cxx;
using namespace std;
class BulkSession;
class BulkLink:public BulkGraphEdge
{
	public:
		BulkLink():BulkGraphEdge() {}
		BulkLink(int from, int to);
		BulkLink(int from, int to, int weight, int capacity);
		BulkLink(BulkGraphEdge& edge);
		bool addSession(BulkSession& session);
		bool deleteSession(int sId);
		void fromHeadToTail(int numPackets, int sessionId);
		bool isUnderConstraints();
	protected:
		slist<BulkSession>* session_;
};
#endif
