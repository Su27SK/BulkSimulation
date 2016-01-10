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
	return this;
}

/**
 * @brief BulkPacket&setPacketType 
 * set the packet size unit 单位
 * @param {unit} type 枚举类型
 */
BulkPacket&BulkPacket::setPacketType(unit type)
{
	this->_type = type;
	return this;
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
	value<<ss;
	ss.clear();
	switch (this->_type) {
		case 1:
			return value + string("Byte");
		case 2:
			return value + string("Kb");
		case 3:
			return value + string("Mb");
		case 4:
			return value + string("Gb");
	}
}

/**
 * @brief getPacketSize 
 * get the packet size (as: 4.2)
 * @return {double}
 */
double BulkPacket::getPacketSize()
{
	return this->_size;
}

/**
 * @brief getPacketUnit 
 * get the packet size's Unit (as:Mb)
 * @return 
 */
unit BulkPacket::getPacketUnit()
{
	return this->_type;
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
		if (isLarge) {
			this->_size = this->_size * degree;
			this->_type = this->_type - degree;
		} else {
			this->_size = this->_size / degree;
			this->_type = this->_type + degree;
		}
		return true;
	} else {
		return false
	}
}
