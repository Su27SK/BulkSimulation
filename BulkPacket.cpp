#include "BulkPacket.h"
BulkPacket::BulkPacket(double size, unit type)
{
	this->_size = size;
	this->_type = type;
}

/**
 * @brief BulkPacket&setPacketSize 
 * set the packet size
 * @param {double} size
 */
BulkPacket&BulkPacket::setPacketSize(double size)
{
	this->_size = size;
	return *this;
}


/**
 * @brief BulkPacket 
 * 显式拷贝构造函数
 * @param {BulkPacket} P
 */
BulkPacket::BulkPacket(const BulkPacket& P)
{
	this->_size = P._size;
	this->_type = P._type;
}

/**
 * @brief BulkPacket 
 * 拷贝构造函数
 * @param {BulkPacket} P
 */
BulkPacket::BulkPacket(BulkPacket& P)
{
	this->_size = P._size;
	this->_type = P._type;
}

/**
 * @brief BulkPacket&setPacketType 
 * set the packet size unit 单位
 * @param {unit} type 枚举类型
 */
BulkPacket&BulkPacket::setPacketType(unit type)
{
	this->_type = type;
	return *this;
}

/**
 * @brief getPacketInfo 
 * get the packet info (as: 4.2Mbytes)
 * @return {string}
 */
string BulkPacket::getPacketInfo()
{
	stringstream ss;
	string value;
	ss<<this->_size;
	ss>>value;
	ss.clear();
	return value + this->getPacketUnit();
}

/**
 * @brief getPacketSize 
 * get the packet size (as: 4.2)
 * @return {double}
 */
double BulkPacket::getPacketSize() const
{
	return this->_size;
}

/**
 * @brief getPacketUnit 
 * get the packet size's Unit (as:Mb)
 * @return {string} 
 */
string BulkPacket::getPacketUnit()
{
	switch (this->_type) {
		case 1:
			return string("Byte");
		case 2:
			return string("Kb");
		case 3:
			return string("Mb");
		case 4:
			return string("Gb");
	}
	return string("Kb");
}

/**
 * @brief 
 * 重载操作符
 * @param {BulkPacket} packet
 *
 * @return 
 */
BulkPacket& BulkPacket::operator = (const BulkPacket& packet)
{
	if (this != &packet) {
		BulkPacket bulkPacketTemp(packet);
		this->_size = bulkPacketTemp._size;
		this->_type = bulkPacketTemp._type;
	}
	return *this;
}

/**
 * @brief ConvertToType 
 * from one unit to anther type;
 * @param {interge} degree (放大或者缩小倍数 base is 10)
 * @param {boolean} isLarge(true:放大, false:缩小)
 *
 * @return {boolean} false/true
 */
bool BulkPacket::ConvertToType(int degree, bool isLarge)
{
	int nowType = isLarge? this->_type + degree: this->_type -degree;
	if (nowType >= 1 && nowType <=4) {
		switch (nowType) {
			case 1:
				this->_type = Byte;
				break;
			case 2:
				this->_type = Kb;
				break;
			case 3:
				this->_type = Mb;
				break;
			case 4:
				this->_type = Gb;
				break;
		}
		if (isLarge) {
			this->_size = this->_size * degree;
		} else {
			this->_size = this->_size / degree;
		}
		return true;
	} else {
		return false;
	}
}

BulkPacket::~BulkPacket()
{
	//cout<<"Decontruct BulkPacket"<<endl;
}
