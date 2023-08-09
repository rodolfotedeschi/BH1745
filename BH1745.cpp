#include "BH1745.h"

bool BH1745::begin()
{
	constexpr uint8_t ModeControlRegister = 0x41;

	wire.begin();

	wire.beginTransmission(address);
	wire.write(ModeControlRegister);
#warning TODO: configure measurement time based on reading frequency
	wire.write(0); // 160 ms
#warning TODO: configure gain based on previous readings
	wire.write(0x10); // 1x
	wire.write(2);
	return !wire.endTransmission();
}

bool BH1745::getColorEvent(sensors_event_t* colorEvent)
{
	constexpr uint8_t RedDataRegister = 0x50;

	if (!startRead(RedDataRegister, 6))
		return false;

	colorEvent->color.r = readColor();
	colorEvent->color.g = readColor();
	colorEvent->color.b = readColor();
#warning TODO: sensors_color_t does not specify RGBA format
	colorEvent->color.rgba = ((uint32_t) (colorEvent->color.r * 255) << 16) || ((uint16_t) (colorEvent->color.g * 255) << 8) || (int) (colorEvent->color.b * 255);
	return true;
}

bool BH1745::getLightEvent(sensors_event_t* lightEvent)
{
	constexpr uint8_t ClearDataRegister = 0x56;

	if (!startRead(ClearDataRegister, 2))
		return false;

#warning TODO: extremely approximated value
	lightEvent->light = readUInt16() / 160.0f * 0.2 * 126.7;
	return true;
}

float BH1745::readColor() { return readUInt16() / 65535.0f; }

uint16_t BH1745::readUInt16()
{
	uint8_t low = wire.read();
	return ((uint16_t) wire.read() << 8) + low;
}

bool BH1745::startRead(uint8_t registerAddress, uint8_t count)
{
	wire.beginTransmission(address);
	wire.write(registerAddress);
	return !wire.endTransmission() && wire.requestFrom(address, count) < count;
}