#ifdef BULKPACKET_H_
#define BULKPACKET_H_
#include<string>
#include<sstream>
#include<iostream>
enum unit{
	Byte = 1,
	Kb = 2,
	Mb = 3
	Gb = 4
};
class BulkPacket
{
	private:
		double _size;
		unit _type;
	public:
		BulkPacket():_size(0), _type(Mb){}
		BulkPacket(double size, unit type);
		BulkPacket& setPacketSize(double size);
		BulkPacket& setPacketType(unit type);
		string getPacketInfo();
		double getPacketSize();
		unit getPacketUnit();
		bool ConvertToType(int degree, bool isLarge = true);
};
#endif
