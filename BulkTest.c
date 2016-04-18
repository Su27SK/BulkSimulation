#include <iostream>
#include <stdlib.h>
#include "BulkFile.h"
#include "Graph.h"
#include "BulkPool.h"
#include "BulkBackPressure.h"
#include "RandomGenerator.h"
#define MAX 10
using namespace std;
int main(int argc, char* argv[])
{
	if (argc != 3) {
		fprintf(stderr, "参数错误 Don't Do that at argv %d\n", argc);
		abort();
		return 0;
	}
	FILE* fp = fopen("Bulk_Log/info.txt", "w+");
	int numNode = atoi(argv[1]); //几个任意不同的起点(有多少个session)
	int demand = atoi(argv[2]);
	fprintf(fp, "numNode:%d, demand:%d\n", numNode, demand);
	RandomGenerator::init(time(NULL));
	Graph* graph = Graph::importGraph("Bulk_Config_File/normalDis2.txt");
	BulkBackPressure test;
	test.setGraph(graph);
	test.init();
	BulkNode** testNode = new BulkNode*[MAX];
	BulkSession** testSession = new BulkSession*[MAX];
	int source[27];
	for (int k = 0; k < 27; k++) {
		source[k] = -1;
	}
	for (int i = 0; i < MAX; i++) {
		testNode[i] = NULL; 
		testSession[i] = NULL;
	}
	srand(unsigned(time(NULL)));
	BulkNode* eNode = test.getNodeById(27);
	for (int i = 0; i < numNode; i++) {
		int Id = rand() % 26;
		while (source[Id] != -1) {
			Id = (Id + 1) % 26;
			if (Id == 0) {
				Id = 1;
			}
		}
		fprintf(fp, "SourceId:%d\n", Id);
		source[Id] = 1;
		testNode[i] = test.getNodeById(Id);
	    testSession[i] = new BulkSession(i + 1, testNode[i], eNode);
		testSession[i]->setDemand(demand);
		test.startSession(*testSession[i]);
	}
	for (int t = 0; t < 1000; t++) {
		cout<<"t:"<<t<<endl;
		test.handle();
		cout<<endl;
		if (!(t%1)) {
			for (int j = 0; j < numNode; j++) {
				test.inputPackets(*testSession[j]);
			}
		}
		test.timer.next();
	}
	return 0;
}
