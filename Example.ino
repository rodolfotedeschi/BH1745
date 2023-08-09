#include "BH1745.h"

BH1745 colorSensor;
// BH1745 colorSensor(BH1745::AddressHigh);
// BH1745 colorSensor(BH1745::AddressLow, &Wire);

void setup()
{
	Serial.begin(9600); // debug

	if (!colorSensor.begin())
		Serial.println("Sensor initialization failed.");
}

void loop()
{
	sensors_event_t colorEvent;

	if (colorSensor.getColorEvent(&colorEvent))
	{
		Serial.print("R: ");
		Serial.print(colorEvent.color.r);
		Serial.print(", G: ");
		Serial.print(colorEvent.color.g);
		Serial.print(", B: ");
		Serial.println(colorEvent.color.b);
	}
	else
		Serial.println("Sensor color reading failed.");

	sensors_event_t lightEvent;

	if (colorSensor.getLightEvent(&lightEvent))
	{
		Serial.print("Light: ");
		Serial.println(lightEvent.light);
	}
	else
		Serial.println("Sensor light reading failed.");

	delay(1000);
}