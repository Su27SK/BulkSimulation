#ifdef _BULKPACKET_H_
#define _BULKPACKET_H_
#include<string>
#include<sstream>
#include<iostream>
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
		BulkPacket():_size(1), _type(Kb){}
		BulkPacket(double size, unit type);
		BulkPacket& setPacketSize(double size);
		BulkPacket& setPacketType(unit type);
		string getPacketInfo();
		double getPacketSize() const;
		string getPacketUnit();
		bool ConvertToType(int degree, bool isLarge = true);
		~BulkPacket();
};
#endif
