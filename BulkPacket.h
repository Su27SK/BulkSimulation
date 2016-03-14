#ifndef _BULKPACKET_H_
#define _BULKPACKET_H_
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;
enum unit{
	Byte = 1,
	Kb = 2,
	Mb = 3,
	Gb = 4
};
class BulkPacket
{
	private:
		double _size;
		unit _type;
	public:
		BulkPacket():_size(1), _type(Kb) {}
		BulkPacket(double size, unit type);
		BulkPacket& setPacketSize(double size);
		BulkPacket& setPacketType(unit type);
		explicit BulkPacket(const BulkPacket& P);
		BulkPacket(BulkPacket& P);
		string getPacketInfo();
		double getPacketSize() const;
		string getPacketUnit();
		BulkPacket& operator = (const BulkPacket& packet);
		bool convertToType(int degree, bool isLarge = true);
		~BulkPacket();
};
#endif
