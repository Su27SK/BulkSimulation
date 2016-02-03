#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include <ext/slist>
#include "BulkGraphEdge.h"
#include "BulkSession.h"
#include "BulkNetwork.h"
using namespace __gnu_cxx;
using namespace std;
class BulkLink:public BulkGraphEdge
{
	private:
		bool _isToTerminal;  //_to是否通向终止点
	public:
		BulkLink():BulkGraphEdge()
		{
			this->_isToTerminal = false;
		}
		BulkLink(int from, int to, bool isTerminal = false);
		BulkLink(int from, int to, int weight, int capacity, bool isTerminal = false);
		void addSession(BulkSession& session);
		void fromHeadToTail(int numPackets, int sessionId);
		bool isUnderConstraints();
	protected:
		slist<BulkSession>* session_;
};
#endif
