#pragma once

#include <Adafruit_Sensor.h>
#include <Wire.h>

class BH1745
{
	uint8_t address;
	TwoWire& wire;

	float readColor();
	uint16_t readUInt16();
	bool startRead(uint8_t registerAddress, uint8_t count);

public:
	static constexpr int AddressLow = 0x38;
	static constexpr int AddressHigh = 0x39;

	BH1745(uint8_t address = AddressLow, TwoWire* wire = &Wire) : address(address), wire(*wire) { }

	bool begin();
	bool getColorEvent(sensors_event_t* colorEvent);
	bool getLightEvent(sensors_event_t* lightEvent);
};